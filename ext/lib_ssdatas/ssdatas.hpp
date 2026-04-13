#ifndef SSUGARY_DATA_STRUCTURES
#define SSUGARY_DATA_STRUCTURES


#include <cstddef>
#include <memory>
#include <stdexcept>
#include <typeinfo>
#include <vector>

namespace sds {
    class Generic {
        private:
            struct Placeholder {
                virtual ~Placeholder() = default;
                virtual const std::type_info& type() = 0;
                virtual std::unique_ptr<Placeholder> clone() = 0;  
            };
        
            template<typename T>
            struct Data : public Placeholder {
                T data;
                Data(T data) : data(std::move(data)) {};
                const std::type_info& type() override {return typeid(T);};
                std::unique_ptr<Placeholder> clone() override {return std::unique_ptr<Placeholder>
                                                              (new Data<T>(data));};
            };

            std::unique_ptr<Placeholder> content;

        public:

            Generic() : content(nullptr){};
        
            template<typename T>
            Generic(T data) : content(new Data<T>(std::move(data))){};
            Generic(const Generic& other) : content(other.content ?
                                                    other.content->clone() : nullptr) {};
            template<typename T>
            T& cast(){
                if(!content ||typeid(T) != content->type())throw std::bad_cast();
                return static_cast<Data<T>*>(content.get())->data;
            }
            inline Generic& operator=(const Generic& other){
                if(this != &other){
                    content = other.content ? other.content->clone() : nullptr;
                }
                return *this;
            }
    };
    template<typename K>
    class HeterogenMap {
        private:
            struct Node {
                K key;
                Generic data;
                Node* next;
                Node(K key, Generic d) : key(key), data(std::move(d)), next(nullptr){};
            };

            std::vector<Node*> table;
            size_t size;
            size_t capacity;

            size_t hashFunc(const K& key) const{
                return std::hash<K>{}(key) % capacity;
            }
            void reHash() {
                size_t oldCapacity = capacity;
                capacity *= 2; 

                std::vector<Node*> newTable(capacity, nullptr);

                for (size_t i{0}; i < oldCapacity; ++i) {
                    Node* current = table[i];
                    
                    while (current != nullptr) {
                        Node* nextNode = current->next; 

                        size_t newIndex = hashFunc(current->key);

                        current->next = newTable[newIndex];
                        newTable[newIndex] = current;

                        current = nextNode; 
                    }
                }

                table = std::move(newTable);
            }

        public:

        HeterogenMap(size_t cap = 16) : capacity(cap), size(0){
            table.resize(capacity, nullptr);
        };
        ~HeterogenMap(){
            for (size_t i = 0; i < capacity; ++i) {
            Node* entry = table[i];
            while (entry != nullptr) {
                Node* prev = entry;
                entry = entry->next;
                delete prev;
            }
        }
    }
        void insert(const K& key, Generic data){

            if(size >= capacity * 0.8) reHash();

            size_t index = hashFunc(key);
            Node* entry = table[index];

            while(entry != nullptr){
                if(entry->key == key){
                    entry->data = std::move(data);
                    return;
                }
                entry = entry->next;
            }


            Node* newNode = new Node(key, std::move(data));
            newNode->next = table[index];
            table[index] = newNode;
            size++;

        };

        Generic* get(const K& key){
            Node* entry = table[hashFunc(key)];

            while(entry != nullptr){
                if(entry->key == key)return &(entry->data);
                entry = entry->next;
            }

            return nullptr;
        }
        bool count(const K& key) const {
            size_t index = hashFunc(key);
            Node* entry = table[index];

            while(entry != nullptr){
                if(entry->key == key) return true;
                entry = entry->next;
            }
            return false;
        }

        inline Generic& operator[](const K& key){
            size_t index = hashFunc(key);
            Node* entry = table[index];

            while(entry != nullptr){
                if(entry->key == key){
                    return entry->data;
                }
                entry = entry->next;
            }

            insert(key, Generic());

            return *(get(key));
        }
        inline Generic operator[](const K& key) const {
            size_t index = hashFunc(key);
            Node* entry = table[index];

            while(entry != nullptr){
                if(entry->key == key){
                    return entry->data;
                }
                entry = entry->next;    
            }
            throw std::out_of_range("Key not found!");
        }

        // Iterators

        struct Iterator {
            std::vector<Node*>* tableRef;
            size_t index;
            Node* currentNode;

            Iterator(std::vector<Node*>* ref, size_t index, Node* current)
            : tableRef(ref), index(index), currentNode(current) {};

            inline Node& operator*(){return *currentNode;}
            inline Node* operator->(){return currentNode;}
            inline Iterator& operator++(){
                if(currentNode != nullptr && currentNode->next != nullptr){
                    currentNode = currentNode->next;
                }
                else{
                    index++;
                    while(index < tableRef->size() && (*tableRef)[index] == nullptr){
                        index++;
                    }

                    if(index >= tableRef->size()){
                        currentNode = nullptr;
                    }
                    else{
                        currentNode = (*tableRef)[index];
                    }
                }
                return *this;
            }
            inline bool operator!=(Iterator other){return currentNode != other.currentNode;}
            inline bool operator==(Iterator other){return currentNode == other.currentNode;}
            
        };
        Iterator end(){
            return Iterator(&table, capacity, nullptr);
        }

        Iterator begin(){
            for(size_t i{0}; i < capacity; i++){
                if(table[i] != nullptr){
                    return Iterator(&table, i, table[i]);
                }
            }
            return end();
        }

    };


};


#endif