#include <iostream>
#include <initializer_list>

//Очередь на основе двунаправленного циклического списка
template <typename T>
struct Element
{
    T number;
    Element* next;
    Element* prev;
};

template <typename T> class QueueBasedOnBidirectionalCyclicLinkedList
{
private:
    Element<T>* head;
    Element<T>* tail;
public:
    //конструктор по умолчанию
    QueueBasedOnBidirectionalCyclicLinkedList();

    //конструктор копирования
    QueueBasedOnBidirectionalCyclicLinkedList(const QueueBasedOnBidirectionalCyclicLinkedList& _object);

    //конструктор перемещения
    QueueBasedOnBidirectionalCyclicLinkedList(QueueBasedOnBidirectionalCyclicLinkedList&& _object);

    //конструктор с использованием списка инициализации
    QueueBasedOnBidirectionalCyclicLinkedList(std::initializer_list<int> _ilist);

    //деконструктор
    ~QueueBasedOnBidirectionalCyclicLinkedList();

    //перегрузка оператора присваивания для копирования
    QueueBasedOnBidirectionalCyclicLinkedList& operator=(const QueueBasedOnBidirectionalCyclicLinkedList& _object);

    //перегрузка оператора присваивания для перемещения
    QueueBasedOnBidirectionalCyclicLinkedList& operator=(QueueBasedOnBidirectionalCyclicLinkedList&& _object);

    //перегрузка оператора присваивания для списка инициализации
    QueueBasedOnBidirectionalCyclicLinkedList& operator=(std::initializer_list<int> _ilist);

    //потоковый вывод
    template <typename T>
    friend std::ostream& operator<<(std::ostream& stream, const QueueBasedOnBidirectionalCyclicLinkedList<T>& _object);

    //функции члены
    //получение размера
    int GetSize();

    void InsertAt(int _value, int _index);
    int RemoveAt(int _index);

    //Методы Push, Pop, Peek
    bool Push(const T& element);
    bool Pop(T& element);
    bool Peek(T& element);
};

//конструктор по умолчанию
template <typename T>
QueueBasedOnBidirectionalCyclicLinkedList<T>::QueueBasedOnBidirectionalCyclicLinkedList()
{
    head = tail = NULL;
}
//консруктор копирования
template <typename T>
QueueBasedOnBidirectionalCyclicLinkedList<T>::QueueBasedOnBidirectionalCyclicLinkedList(const QueueBasedOnBidirectionalCyclicLinkedList& _object)
{
    if (_object.head == NULL)
    {
        head = tail = NULL;
        return;
    }
    Element<T>* temp = _object.head;
    while (temp != _object.tail)
    {
        this->Push(temp->number);
        temp = temp->prev;
    }
    this->Push(temp->number);
}
//конструктор перемещения
template <typename T>
QueueBasedOnBidirectionalCyclicLinkedList<T>::QueueBasedOnBidirectionalCyclicLinkedList(QueueBasedOnBidirectionalCyclicLinkedList&& _object)
{
    if (_object.head == NULL)
    {
        head = tail = NULL;
        return;
    }
    head = _object.head;
    tail = _object.tail;
    _object.head = _object.tail = NULL;
}
//конструктор для листа инициализации
template <typename T>
QueueBasedOnBidirectionalCyclicLinkedList<T>::QueueBasedOnBidirectionalCyclicLinkedList(std::initializer_list<int> _ilist)
{
    for (const auto& element : _ilist)
        this->Push(element);
}

//деструктор
template <typename T>
QueueBasedOnBidirectionalCyclicLinkedList<T>::~QueueBasedOnBidirectionalCyclicLinkedList()
{
    if (head == NULL) return;
    int temp;
    while (this->GetSize() > 0)
    {
        this->Pop(temp);
    }
    head = tail = NULL;
}
//операция присвоение
template <typename T>
QueueBasedOnBidirectionalCyclicLinkedList<T>& QueueBasedOnBidirectionalCyclicLinkedList<T>::operator=(const QueueBasedOnBidirectionalCyclicLinkedList& _object)
{
    if (this == &_object || _object.head == NULL)
        return *this;
    int pop;
    for (int size = this->GetSize(); size > 0; size--)
        this->Pop(pop);
    Element<T>* temp = _object.head;
    while (temp != _object.tail)
    {
        this->Push(temp->number);
        temp = temp->prev;
    }
    this->Push(temp->number);
    return *this;
}
//операция присвоение с перемещением
template <typename T>
QueueBasedOnBidirectionalCyclicLinkedList<T>& QueueBasedOnBidirectionalCyclicLinkedList<T>::operator=(QueueBasedOnBidirectionalCyclicLinkedList&& _object)
{
    if (this == &_object || _object.head == NULL)
        return *this;
    head = _object.head;
    tail = _object.tail;
    _object.head = _object.tail = NULL;
    return *this;
}

template<typename T>
QueueBasedOnBidirectionalCyclicLinkedList<T>& QueueBasedOnBidirectionalCyclicLinkedList<T>::operator=(std::initializer_list<int> _ilist)
{
    int temp;
    for(int size = this->GetSize();  size > 0; size--)
        this->Pop(temp);
    for (const auto& element : _ilist)
        this->Push(element);
    return *this;
}

//получение размера
template<typename T>
int QueueBasedOnBidirectionalCyclicLinkedList<T>::GetSize()
{
    int i = 0;
    Element<T>* temp = tail;
    if (head == NULL) return 0;
    while (temp != head)
    {
        i++;
        temp = temp->next;
    }
    return i + 1;
}

template<typename T>
void QueueBasedOnBidirectionalCyclicLinkedList<T>::InsertAt(int _value, int _index)
{
    int size = this->GetSize() + 1;
    QueueBasedOnBidirectionalCyclicLinkedList<int>* temp_obj{ std::move(this) };
    int tmp;
    if (_index <= size)
        for (int i = 0; i < size; i++)
        {
            if (_index == i)
            {
                this->Push(_value);
                continue;
            }
            temp_obj->Pop(tmp);
            this->Push(tmp);
        }
}

template<typename T>
int QueueBasedOnBidirectionalCyclicLinkedList<T>::RemoveAt(int _index)
{
    int size = this->GetSize();
    QueueBasedOnBidirectionalCyclicLinkedList<int>* temp_obj{ std::move(this) };
    int removedElement = 0;
    int tmp;
    if (_index <= size)
        for (int i = 0; i < size; i++)
        {
            if (_index == i)
            {
                temp_obj->Pop(removedElement);
                continue;
            }
            temp_obj->Pop(tmp);
            this->Push(tmp);
        }
    return removedElement;
}

// Метод для добавления элемента в конец очереди
template <typename T>
bool QueueBasedOnBidirectionalCyclicLinkedList<T>::Push(const T& element)
{
    Element<T>* temp = new Element<int>;
    temp->number = element;

    if (head != NULL)
    {
        temp->next = tail;
        temp->prev = head;

        tail->prev = temp;
        head->next = temp;
        tail = temp;
    }
    else temp->next = temp->prev = head = tail = temp;
    return true;
}

// Метод для удаления элемента из начала очереди
template <typename T>
bool QueueBasedOnBidirectionalCyclicLinkedList<T>::Pop(T& element)
{
    if (head == tail)
    {
        if (head == NULL) return false;
        element = head->number;
        delete head;
        head = tail = NULL;
        return true;
    }
    element = head->number;
    head = head->prev;
    delete head->next;
    head->next = tail;
    tail->prev = head;
    return true;
}

// Метод для просмотра элемента в начале очереди
template <typename T>
bool QueueBasedOnBidirectionalCyclicLinkedList<T>::Peek(T& element)
{
    if (head == NULL) return false;
    element = head->number;
    return true;
}


//перегруженный оператр вывода
template<typename T>
std::ostream& operator<<(std::ostream& stream, const QueueBasedOnBidirectionalCyclicLinkedList<T>& _object)
{
    if (_object.head == NULL) return stream << "Queue is empty!";
    Element<T>* temp = _object.head;
    while (temp != _object.tail)
    {
        stream << temp->number << " ";
        temp = temp->prev;
    }
    return stream << temp->number << std::endl;
}

int main()
{
    int peekElement = 0;
    int popElement = 0;

    QueueBasedOnBidirectionalCyclicLinkedList<int> default_queue;// Конструктор по умолчанию
    QueueBasedOnBidirectionalCyclicLinkedList<int> initialization_queue = { 1, 2, 3, 4, 5 };// Конструктор с использованием списка инициализации
    QueueBasedOnBidirectionalCyclicLinkedList<int> copy_queue{ initialization_queue };// Конструктор кпирования
    QueueBasedOnBidirectionalCyclicLinkedList<int> temp_queue{ copy_queue };// Конструктор кпирования
    QueueBasedOnBidirectionalCyclicLinkedList<int> move_queue{ std::move(temp_queue) };//конструктор переноса

    //провера вывода GetSize()
    std::cout << "Size of default_queue default constructor: " << default_queue.GetSize() << std::endl;
    std::cout << "Size of initialization_queue initialization_list: " << initialization_queue.GetSize() << std::endl;
    std::cout << "Size of copy_queue copy constructor: " << copy_queue.GetSize() << std::endl;
    std::cout << "Size of move_queue move constructor: " << move_queue.GetSize() << std::endl << std::endl;

    default_queue = initialization_queue;

    std::cout << default_queue;

    //проверка вывода через переруженный оператор потокового вывода 
    std::cout << "Elements of initialization list: " << initialization_queue << std::endl;

    //тестирование заполнения масива
    default_queue = { 1,2,3,4 };
    copy_queue = { 2,3,4 };

    //вывод элементов заполненых массивов 
    std::cout << "filled new elements of default_queue: ";
    std::cout << default_queue;
    std::cout << "filled new elements of copy_queue: ";
    std::cout << copy_queue << std::endl;

    //проверка перегруженных операторов Pop, Push, Peek
    //-------------------------------------------------------------
    std::cout << "Push >> Peek >> Pop:" << std::endl;
    std::cout << "All elements of default_queue before Push: ";
    std::cout << default_queue;
    default_queue.Push(10);
    std::cout << "All elements of default_queue after Push: ";
    std::cout << default_queue;
    std::cout << "Peeked element of default_queue: ";
    default_queue.Peek(peekElement);
    std::cout << peekElement << std::endl;
    default_queue.Pop(popElement);
    std::cout << "Popped back element of default_queue: ";
    std::cout << popElement << std::endl;
    std::cout << "All elements of default_queue after Pop: ";
    std::cout << default_queue << std::endl;

    //проверка методов InsertAt + RemoveAt
    std::cout << "InsertAt >> RemoveAt:" << std::endl;
    std::cout << "All elements of default_queue before InsertAt(1): ";
    std::cout << default_queue;
    std::cout << "All elements of default_queue after InsertAt(1000, 1): ";
    default_queue.InsertAt(1000, 1);
    std::cout << default_queue;
    std::cout << "All elements of default_queue after RemoveAt(2): ";
    default_queue.RemoveAt(3);
    std::cout << default_queue;
    //-------------------------------------------------------------
    return 0;
}