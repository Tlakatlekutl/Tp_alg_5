#include <iostream>
#include <string>
#define MUL_BUFFER 4
using namespace std;

class Stack {
    public:
        explicit Stack(int size = 0): top_(0), buffer_size_(size) {
            buf_ = new char[buffer_size_];
        }
        ~Stack() {
            delete[] buf_;
        }
        char Pop() {
            top_--;
            char result = buf_[top_];

            return result;
        }
        void Push(char value) {
            buf_[top_] = value;
            if (top_+1 == buffer_size_)
                AddBuffer();
            if (top_ == 0)
                bottom_value_ = value;
            top_++;
        }
        char GetTopValue() {
            return buf_[top_-1];
        }
        int GetStackSize() {
            return top_;
        }
        void ClearStack() {
            top_ = 0;
        }
    private:
        int buffer_size_;
        int top_;
        char *buf_;
        char bottom_value_;
        void AddBuffer() {
            char *new_buf_ = new char[buffer_size_*MUL_BUFFER];
            for (int i = 0; i < buffer_size_; i++)
                new_buf_[i] = buf_[i];
            delete[] buf_;
            buffer_size_*=MUL_BUFFER;
            buf_=new_buf_;
        }
};

int main() {
    string input, output, temp;
    cin>>input>>output;
    Stack stk(10);
    int i = 0, output_pos = 0;
    for (i; input[i] != '\0'; i++) {
        stk.Push(input[i]);           // Идем по элементам первого слова, занося буквы в массив
        if (input[i] == output[output_pos]) { //Если встертились 
                                           //совпадающие буквы, проверим на соответсвие содержимого
                                           //стека со следующей подстрокой
            while (stk.GetStackSize() && (stk.GetTopValue() == output[output_pos])) {
                output_pos++;
                stk.Pop();
            }
        }
    }
    if (!stk.GetStackSize()) {//Если все подстроки уже найдены
        cout<<"YES";
        return 0;
    } else {//Иначе, подстрока может идти до конца слова, проверим это
        for (int j = stk.GetStackSize(); j > 0; j--){
            if (stk.Pop() != output[i-j]) {
                cout<<"NO";
                return 0;
            }
        }
    }
    cout<<"YES";

    
    return 0;
}