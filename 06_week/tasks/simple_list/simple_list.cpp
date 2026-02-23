#include <string>
#include <cstddef>
#include <algorithm>

class SimpleList {
private:
    struct Node {
        std::string data;
        Node* next;
        Node* prev;
        
        Node(const std::string& value);
        Node(std::string&& value);
    };
    
    Node* head;   // фиктивный узел (sentinel)
    size_t count; // количество элементов
    
    void Unlink(Node* node);
    void LinkAfter(Node* new_node, Node* after_this);
    void LinkBefore(Node* new_node, Node* before_this);
    
public:

    // Конструкторы
    SimpleList();
    SimpleList(const SimpleList& other);
    SimpleList(SimpleList&& other) noexcept;

    // Диструкторы
    ~SimpleList();

    // Операторы
    SimpleList& operator=(const SimpleList& other);
    SimpleList& operator=(SimpleList&& other) noexcept;
    
    // Методы
    void Swap(SimpleList& other) noexcept;
    size_t Size() const;
    bool Empty() const;

    void PushBack(const std::string& value);
    void PushBack(std::string&& value);
    void PopBack();
    
    void PushFront(const std::string& value);
    void PushFront(std::string&& value);
    void PopFront();
    
    void Clear();
    
    std::string& Front();
    const std::string& Front() const;
    
    std::string& Back();
    const std::string& Back() const;
};

// Свободная функция swap
void Swap(SimpleList& lhs, SimpleList& rhs) noexcept;

// Конструкторы узла
SimpleList::Node::Node(const std::string& value) 
    : data(value), next(nullptr), prev(nullptr) {}

SimpleList::Node::Node(std::string&& value) 
    : data(std::move(value)), next(nullptr), prev(nullptr) {}
    

// Приватные вспомогательные методы

// Удаляет узел из списка
void SimpleList::Unlink(Node* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
    --count;
}

// Вставляет узел после указанного
void SimpleList::LinkAfter(Node* new_node, Node* after_this) {
    new_node->prev = after_this;
    new_node->next = after_this->next;
    after_this->next->prev = new_node;
    after_this->next = new_node;
    ++count;
}

// Вставляет узел перед указанным
void SimpleList::LinkBefore(Node* new_node, Node* before_this) {
    LinkAfter(new_node, before_this->prev);
}

// Конструктор по умолчанию
SimpleList::SimpleList() : count(0) {
    head = new Node(std::string());
    head->next = head;
    head->prev = head;
}

// Копирующий конструктор
SimpleList::SimpleList(const SimpleList& other) : SimpleList() {
    Node* current = other.head->next;
    while (current != other.head) {
        PushBack(current->data);
        current = current->next;
    }
}

// Перемещающий конструктор
SimpleList::SimpleList(SimpleList&& other) noexcept 
    : head(other.head), count(other.count) {
    other.head = new Node(std::string());
    other.head->next = other.head;
    other.head->prev = other.head;
    other.count = 0;
}

// Деструктор
SimpleList::~SimpleList() {
    Clear();
    delete head;
}

// Копирующее присваивание
SimpleList& SimpleList::operator=(const SimpleList& other) {
    if (this != &other) {
        SimpleList temp(other);
        Swap(temp);
    }
    return *this;
}

// Перемещающее присваивание
SimpleList& SimpleList::operator=(SimpleList&& other) noexcept {
    if (this != &other) {
        Clear();
        delete head;
        
        head = other.head;
        count = other.count;
        
        other.head = new Node(std::string());
        other.head->next = other.head;
        other.head->prev = other.head;
        other.count = 0;
    }
    return *this;
}

// Обмен содержимым с другим списком
void SimpleList::Swap(SimpleList& other) noexcept {
    std::swap(head, other.head);
    std::swap(count, other.count);
}

// Получение размера списка
size_t SimpleList::Size() const {
    return count;
}

// Проверка, пуст ли список
bool SimpleList::Empty() const {
    return count == 0;
}

// Вставка в конец
void SimpleList::PushBack(const std::string& value) {
    Node* new_node = new Node(value);
    LinkBefore(new_node, head);
}

void SimpleList::PushBack(std::string&& value) {
    Node* new_node = new Node(std::move(value));
    LinkBefore(new_node, head);
}

// Удаление последнего элемента
void SimpleList::PopBack() {
    if (!Empty()) {
        Unlink(head->prev);
    }
}

// Вставка в начало
void SimpleList::PushFront(const std::string& value) {
    Node* new_node = new Node(value);
    LinkAfter(new_node, head);
}

void SimpleList::PushFront(std::string&& value) {
    Node* new_node = new Node(std::move(value));
    LinkAfter(new_node, head);
}

// Удаление первого элемента
void SimpleList::PopFront() {
    if (!Empty()) {
        Unlink(head->next);
    }
}

// Очистка списка
void SimpleList::Clear() {
    while (!Empty()) {
        PopFront();
    }
}

// Доступ к первому элементу
std::string& SimpleList::Front() {
    return head->next->data;
}

const std::string& SimpleList::Front() const {
    return head->next->data;
}

// Доступ к последнему элементу
std::string& SimpleList::Back() {
    return head->prev->data;
}

const std::string& SimpleList::Back() const {
    return head->prev->data;
}

// Свободная функция swap
void Swap(SimpleList& lhs, SimpleList& rhs) noexcept {
    lhs.Swap(rhs);
}