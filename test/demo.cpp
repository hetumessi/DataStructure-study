//
// Created by 徐绍骞 on 2022/4/7.
//
#include <iostream>
#include <sstream>
#include <string>

class Node {
private:
    /* data */
    int key;
    int value;
    Node* prev;
    Node* next;

public:
    Node(int key, int value) {
        this->key = key;
        this->value = value;
        this->next = nullptr;
        this->prev = nullptr;
    }

    ~Node(){};

    int get_key() { return this->key; };
    int get_value() { return this->value; };
    Node* get_prev() { return this->prev; };
    Node* get_next() { return this->next; };
    void set_key(int key) { this->key = key; };
    void set_value(int value) { this->value = value; };
    void set_prev(Node* prev) { this->prev = prev; };
    void set_next(Node* next) { this->next = next; };

    std::string to_string() {
        std::ostringstream ss;
        // ss << "@"<< this << "{key: " << this->key << ", value: " << this->value << "}";
        ss << "{key: " << this->key << ", value: " << this->value << "}";
        return ss.str();
    }
};

class DoubleLinkList {
private:
    int size;
    int capacity;
    Node* head;
    Node* tail;

    Node* add_head(Node*);
    Node* add_tail(Node*);
    Node* del_head();
    Node* del_tail();
    Node* _remove(Node* node=nullptr);

public:
    DoubleLinkList(int capacity = 0xffff) {
        this->capacity = capacity;
        this->size = 0;
        this->head = nullptr;
        this->tail = nullptr;
    };
    ~DoubleLinkList(){};

    Node* pop();
    Node* append(Node*);
    Node* append_front(Node*);
    Node* remove(Node* node=nullptr);

    int get_capacity() { return this->capacity; };
    void set_capacity(int capacity) { this->capacity = capacity; };
    int get_size() { return this->size; };

    std::string to_string() {
        /*  ostringstream是C++的一个字符集操作模板类，定义在sstream.h头文件中。
            ostringstream类通常用于执行C风格的串流的输出操作，格式化字符串，避免申请大量的缓冲区，可替代sprintf
            有时候，我们需要格式化一个字符串，但通常并不知道需要多大的缓冲区。为了保险常常申请大量的缓冲区以防止缓冲区过小造成字符串无法全部存储。
            这时我们可以考虑使用ostringstream类，该类能够根据内容自动分配内存，并且其对内存的管理也是相当的到位。
            取得std::ostringstream里的内容可以通过str()和str(string&)成员函数。
            示例：
            ostringstream ostr1; // 构造方式1
            ostringstream ostr2("abc"); // 构造方式2
            ostr1 << "ostr1" << 2012 << endl; // 格式化，此处endl也将格式化进ostr1中
            cout << ostr1.str()<<endl;
            cout<<ostr2.str()<<endl;

        */
        std::ostringstream ss;
        Node* p = this->head;
        int num = this->size;
        while (p != nullptr && num --) {
            ss << p->to_string();
            if (p->get_next() != nullptr) {
                ss << "->";
            }
            p = p->get_next();
        }
        return ss.str();
    }
};
#include <map>

class LFUNode: public Node{
public:
    int freq;
    LFUNode(int key, int value): Node(key, value) {
        this->freq = 0;
    };
    ~LFUNode(){}
};

class LFUCache {
private:
    int capacity;
    int size;
    std::map<int, LFUNode*> map;
    std::map<int, DoubleLinkList*> freq_map;

    void update_freq(LFUNode* node);

public:
    LFUCache(int capacity=0xffff): capacity(0) {
        this->capacity = capacity;
        this->size = 0;
    };

    int get(int key);
    Node* put(int key, int value);
    std::string to_string();

    ~LFUCache(){

    };
};
Node* DoubleLinkList::add_head(Node* node){
    if(this->head == nullptr){
        node->set_prev(nullptr);
        node->set_next(nullptr);
        this->head = node;
        this->tail = node;
    } else {
        node->set_next(this->head);
        this->head->set_prev(node);
        this->head = node;
        this->head->set_prev(nullptr);
    }
    this->size += 1;
    return node;
}
Node* DoubleLinkList::add_tail(Node* node){
    if(this->tail == nullptr){
        node->set_prev(nullptr);
        node->set_next(nullptr);
        this->head = node;
        this->tail = node;
    } else {
        this->tail->set_next(node);
        node->set_prev(this->tail);
        this->tail = node;
        this->tail->set_next(nullptr);
    }
    this->size += 1;
    return node;
}

Node* DoubleLinkList::del_head(){
    if(this->head == nullptr){
        return nullptr;
    }
    Node* node = this->head;
    if(this->head->get_next() != nullptr){
        this->head->get_next()->set_prev(nullptr);
        this->head = this->head->get_next();
    } else {
        this->head = nullptr;
        this->tail = nullptr;
    }
    this->size -= 1;
    return node;
}

Node* DoubleLinkList::del_tail(){
    if (this->tail == nullptr){
        return nullptr;
    }
    Node* node = this->tail;
    if (this->tail->get_prev() != nullptr){
        this->tail = this->tail->get_prev();
        this->tail->set_next(nullptr);
    } else {
        this->tail = nullptr;
        this->head = nullptr;
    }
    this->size -= 1;
    return node;
}

Node* DoubleLinkList::_remove(Node* node){
    if (node == nullptr){
        node = this->tail;
    }
    if (node == this->head){
        return this->del_head();
    }

    if (node == this->tail){
        return this->del_tail();
    }

    node->get_prev()->set_next(node->get_next());
    node->get_next()->set_prev(node->get_prev());
    this->size -= 1;
    return node;
}

Node* DoubleLinkList::pop(){
    return this->del_head();
}

Node* DoubleLinkList::append(Node* node){
    return this->add_tail(node);
}

Node* DoubleLinkList::append_front(Node* node){
    return this->add_head(node);
}

Node* DoubleLinkList::remove(Node* node){
    return this->_remove(node);
}
void LFUCache::update_freq(LFUNode* node){
    int freq = node->freq;
    this->freq_map.find(freq)->second->remove((Node*)node);
    if(this->freq_map.find(freq)->second->get_size() == 0){
        DoubleLinkList* list = this->freq_map.find(freq)->second;
        this->freq_map.erase(freq);
        delete list;
    }
    freq += 1;
    node->freq = freq;
    std::map<int,DoubleLinkList*>::iterator it = this->freq_map.find(freq);
    if (it == this->freq_map.end()){
        std::map<int,DoubleLinkList*>::iterator it = this->freq_map.begin();
        this->freq_map.insert(std::pair<int, DoubleLinkList*>(freq, new DoubleLinkList()));
    }
    this->freq_map.find(freq)->second->append((Node*)node);
}

int LFUCache::get(int key){
    std::map<int,LFUNode*>::iterator it = this->map.find(key);
    if (it == this->map.end()){
        return -1;
    }
    LFUNode* node = this->map.find(key)->second;
    this->update_freq(node);
    return node->get_value();
}

Node* LFUCache::put(int key, int value){
    if(this->capacity == 0){
        return nullptr;
    }
    std::map<int,LFUNode*>::iterator it = this->map.find(key);
    if (it != this->map.end()){
        LFUNode* node = this->map.find(key)->second;
        node->set_value(value);
        this->update_freq(node);
        return node;
    } else {
        if (this->size == this->capacity) {
            int min_freq = 0xffff;
            /* map的四种遍历方式
                值传递遍历：for(pair it:map)或for(auto i:map)
                引用传递遍历：for(const pair&it:map)或for(auto&it:map)
                使用迭代器遍历：for(map::iterator it=map.begin();it!=map.end();it++)或
                             for(auto it=map.begin();it!=map.end();it++)
                结构化绑定(c++17特性)：值传递for(auto [k,v]:map)   (k,v对应元素的first和second成员)
                                    引用传递for(auto&[k,v]:map)
             */
            for(std::map<int,DoubleLinkList*>::iterator it=this->freq_map.begin();it!=this->freq_map.end();it++){
                // min()是algorithm.h的库函数，用于从给定的两个值中找到最小值，它接受两个值并返回最小值，如果两个值相同则返回第一个值。
                min_freq = std::min(min_freq, it->first);
            }
            Node *node = this->freq_map.find(min_freq)->second->pop();
            this->map.erase(node->get_key());
            delete node;
        }
        LFUNode *node = new LFUNode(key, value);
        node->freq = 1;
        std::map<int,LFUNode*>::iterator it = this->map.begin();
        this->map.insert(it, std::pair<int, LFUNode*>(key, node));
        std::map<int,DoubleLinkList*>::iterator p = this->freq_map.find(node->freq);
        if (p == this->freq_map.end()){
            std::map<int,DoubleLinkList*>::iterator it = this->freq_map.begin();
            this->freq_map.insert(it, std::pair<int, DoubleLinkList*>(node->freq, new DoubleLinkList()));
        }
        this->freq_map.find(node->freq)->second->append(node);
        return (Node*)node;
    }
}

std::string LFUCache::to_string(){
    std::ostringstream ss;
    ss << "*********************\n";
    for(std::map<int,DoubleLinkList*>::iterator item=this->freq_map.begin();item!=this->freq_map.end();item++){
        ss << item->first << ": " << item->second->to_string() << "\n";
    }
    return ss.str();
}
void test_lfu_cache(){
    LFUCache cache(3);
    cache.put(1, 1);
    cache.put(2, 2);
    cache.put(3, 3);
    cache.put(4, 4);
    std::cout << cache.to_string() << std::endl;
    std::cout << cache.get(1) << std::endl;
    std::cout << cache.to_string() << std::endl;
    std::cout << cache.get(3) << std::endl;
    std::cout << cache.to_string() << std::endl;
    cache.put(5, 5);
    std::cout << cache.to_string() << std::endl;
    cache.put(2, 2);
    std::cout << cache.to_string() << std::endl;
    cache.put(1, 1);
    std::cout << cache.to_string() << std::endl;
    std::cout << cache.get(2) << std::endl;
    std::cout << cache.to_string() << std::endl;
    std::cout << cache.get(1) << std::endl;
    std::cout << cache.to_string() << std::endl;
}