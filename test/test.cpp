//
// Created by 徐绍骞 on 2022/3/2.
//
#include<iostream>
#include<cstdlib>
#include<pthread.h>
#include<chrono>
#include<list>
#include<vector>
#include<thread>
#define POOLSZIE 100
class Task{
private:
    bool done;
    Elementype result;
    pthread_mutex_t mutex{};
    pthread_cond_t cond{};
public:
    Task(){
        this->done=false;
        this->result=0;
        pthread_mutex_init(&mutex,nullptr);
        pthread_cond_init(&cond,nullptr);
    }
    ~Task(){
        std::cout<<"任务已销毁"<<std::endl;
    }
    void set_result(Elementype);
    Elementype getresult();
    static Elementype collable();
};
class ThreadSafeQueue{
private:
    std::list<Task*>*queue;
    int queue_size;
    pthread_mutex_t mutex{};
    pthread_cond_t cond{};
public:
    ThreadSafeQueue(){
        this->queue_size=0;
        this->queue=new  std::list<Task*>;
        pthread_mutex_init(&mutex,nullptr);
        pthread_cond_init(&cond, nullptr);
    }
    ~ThreadSafeQueue(){
        for(auto i:*this->queue)delete(i);
    }
    int getsize() const;
    void put(Task*);
    Task*pop();
};
void*wrapper(void*threadpool);
class ThreadPool{
private:
    int pthread_size;
    bool flag;
    ThreadSafeQueue*Tqueue;
    pthread_t*pthread_pool{};
public:
    ThreadPool(){
        this->pthread_size=0;
        this->flag=true;
        this->Tqueue=new ThreadSafeQueue();
        this->pthread_pool=(pthread_t*)malloc(POOLSZIE*sizeof(pthread_t));
        for(int i=0;i<POOLSZIE;i++){
            pthread_create(&pthread_pool[i],nullptr,wrapper,nullptr);
        }
    }
    ~ThreadPool(){
        delete this->pthread_pool;
        delete this->Tqueue;
    }
    void process(),batch_put(const std::vector<Task*>&),join(),start(),stop();
};
void*wrapper(void*threadpool){
    auto pool=(ThreadPool*)threadpool;
    pool->process();
    return nullptr;
}
void Task::set_result(Elementype setvalue){
    pthread_mutex_lock(&this->mutex);
    this->result=setvalue;
    pthread_mutex_unlock(&this->mutex);
    pthread_cond_signal(&this->cond);
}
Elementype Task::getresult(){
    Elementype getvalue;
    pthread_mutex_lock(&this->mutex);
    while(!this->done)pthread_cond_wait(&this->cond,&this->mutex);
    getvalue=this->result;
    pthread_mutex_unlock(&this->mutex);
    return getvalue;
}
Elementype Task::collable(){
    std::chrono::milliseconds ms=std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
            );
    return (Elementype)ms.count()/1000;
}
int ThreadSafeQueue::getsize()const{
    return this->queue_size;
}
void ThreadSafeQueue::put(Task*input){
    pthread_mutex_lock(&this->mutex);
    this->queue->push_back(input);
    this->queue_size++;
    pthread_mutex_unlock(&this->mutex);
    pthread_cond_signal(&this->cond);
}
Task*ThreadSafeQueue::pop(){
    pthread_mutex_lock(&this->mutex);
    while(!this->getsize())pthread_cond_wait(&cond,&mutex);
    Task*poptask=this->queue->front();
    this->queue->pop_front();
    this->queue_size--;
    pthread_mutex_unlock(&this->mutex);
    return poptask;
}
void ThreadPool::process(){
    Task*processtask;
    while(this->flag){
        processtask=this->Tqueue->pop();
        processtask->set_result(processtask->getresult());
    }
}
void ThreadPool::batch_put(const std::vector<Task*>&input){
    for(auto&i:input)this->Tqueue->put(i);
}
void ThreadPool::join(){
    for(int i=0;i<this->pthread_size;i++)pthread_join(this->pthread_pool[i],nullptr);
}
void ThreadPool::start(){}
void ThreadPool::stop(){
    this->flag=false;
}
//int main(){
//    auto*pool=new ThreadPool();
//    pool->start();
//    std::vector<Task*>inputvector;
//    for(int i=0;i<POOLSZIE;i++)inputvector.push_back(new Task);
//    pool->batch_put(inputvector);
//    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//    for(auto&i:inputvector)std::cout<<i->getresult()<<' ';
//    pool->stop();
//    pool->join();
//}
/* 整个执行流程：线程池的任务处理流程就是：
 * 开辟线程 -> 阻塞线程 -> 任务入队 -> 唤醒线程 -> 执行线程 -> 阻塞线程.
 * 1.调用ThreadPool构造函数创建线程池
 * 2.ThreadPool构造函数创建多个线程时，并在创建时调用wrapper
 *     2.0.假设线程创建后直接进行调度
 *     2.1.wrapper调用this->process()
 *     2.2.this->process()调用this->Tqueue->pop()
 *     2.3.此时Tqueue为空，因此this->Tqueue->cond上锁，该线程阻塞
 * 3.ThreadPool创建的线程阻塞，主线程继续执行，将任务批量入队
 *     3.1.一个任务进入Tqueue后(put)唤醒一个阻塞进程
 *     3.2.阻塞进程完成process()，将结果(线程执行结束时间点到1970.1.1间的秒数)写入task
 *     3.3.wrapper结束，线程执行结束
 * 4.主线程完成后sleep一秒，将线程池关闭，剩下的线程(如果还有没任务可执行的)阻塞
 * 5.在主线程中join，确保线程池中线程先于主线程完成
 */