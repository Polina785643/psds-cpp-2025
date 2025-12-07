 #include <stdexcept>

/*Функция обмена указателей*/

template<typename T>
void SwapPtr(T*& ptr1, T*& ptr2) {
    T* temp = ptr1;
    ptr1 = ptr2;
    ptr2 = temp;
}

// Явная инстанциация для нужных типов
template void SwapPtr<int>(int*&, int*&);
template void SwapPtr<const int>(const int*&, const int*&);
template void SwapPtr<int*>(int**&, int**&);