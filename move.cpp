#include <stdio.h>
#include <memory>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <vector>

using namespace std;
static const uint32_t MAX_LEN = 10000;

class Context {
public:
    char *buffer;
    Context() {
        buffer = (char*)malloc(MAX_LEN*sizeof(char));
        cout << "constructor" << endl;
    }

    Context(Context& ctx) {
        //拷贝构造函数，内存复制，效率低
        buffer = (char*)malloc(MAX_LEN*sizeof(char));
        strcpy(buffer, ctx.buffer);
        cout << "copy constructor" << endl;
    }

    Context(Context&& original_ctx) {
        //移动构造函数，没有内存复制，效率高
        buffer = original_ctx.buffer;
        original_ctx.buffer = nullptr; //掏空
        cout << "move constructor" << endl;
    }
};

int main() {
    const char *response = "ee67e3f91573510a6b520ed1381450e5";
    Context ctx;
    strcpy(ctx.buffer, response);

    //调用拷贝构造函数，完了ctx依然可以使用
    Context dup_ctx(ctx);
    printf("%s\n", ctx.buffer);

    //调用移动构造函数，完了ctx被掏空，不要再使用
    Context dup_ctx_2(std::move(ctx));
    //Error: printf("%s\n", ctx.buffer);

    return 1;
}
