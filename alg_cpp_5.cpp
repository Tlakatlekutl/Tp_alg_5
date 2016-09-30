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
        char GetBottomValue() {
            return bottom_value_;
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
    string input, output;
    cin>>input>>output;
    Stack stk(8);
    int i = 0;
    for ( i; input[i]!='\0'; i++) {
        if (input[i] != output[i]) { //если буквы на одной позиции разные
            if (stk.GetStackSize()!=0 && (output[i] == stk.GetBottomValue())) {
                stk.Push(input[i]);
                for (int j = stk.GetStackSize(); j > 0; j--) {
                    if (stk.Pop() != output[i-j+1]) {
                        cout <<"NO";
                        return 0;
                    }
                }
            } else {
                stk.Push(input[i]);
            }
        }
        else if ((input[i] == output[i]) && stk.GetStackSize()) { //находим подстроку полученную переворотом aBCd и aCBd
            if (stk.GetBottomValue() != output[i-1]) {
                stk.Push(input[i]);
            }
        }
    }
    if (!stk.GetStackSize()) {
        cout<<"YES";
        return 0;
    } else {
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