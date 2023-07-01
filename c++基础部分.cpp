#include<iostream>
#include<typeinfo>
using namespace std;

/*
new和delete
new和malloc的区别是什么？
delete和free的区别是什么？

malloc和free，称作C的库函数
new和delete，称作运算符

malloc只负责开辟内存，不负责初始化；
new不仅可以做内存开辟，还可以做内存初始化操作

malloc开辟内存失败，是通过返回值和nullptr做比较；
而new开辟内存失败，是通过抛出bad_alloc类型的异常来判断的。

new在开辟内存的时候，是指定类型的，所以它的返回值不需要进行类型强转
而malloc在开辟内存的时候，只是根据字节开辟内存，不管内存当中放什么类型的数据，返回值是void*，因此要对返回值进行类型的转换

delete在释放空间的时候，单个元素不加[]；释放数组空间的时候，要加[] 
*/
#if 0
int main01()
{
	//new有多少种？		4种
	int* p1 = new int(20);	//抛出异常

	int* p2 = new (nothrow) int;	//它的内存开辟失败和malloc相同，和nullptr进行比较	
	//不抛出异常
	const int* p3 = new const int(40);	//在堆上生成常量变量(或者对象)

	//定位new
	int data = 0;
	int* p4 = new (&data) int(50);
	//在指定的内存上，划分出4字节大小的内存，初值为50



	int* p = (int*)malloc(sizeof(int));
	if (p == nullptr)
	{
		return -1;
	}
	*p = 20;
	free(p);


	int* p1 = new int(20);	//括号里面是初始值
	delete p1;

	int* q = (int*)malloc(sizeof(int) * 20);
	if (q == nullptr)
	{
		return -1;
	}
	free(q);

	//int* q1 = new int[20];	//在堆上只负责开辟数组，数字的元素不进行初始化
	int* q1 = new int[20]();	//20个int sizeof(int)*20  数组的元素初始化为0
	delete[]q1;


	return 0;

}


/*
const，一级指针，引用的结合应用
*/
int main()
{
	//写一句代码，在内存0x0018ff44处写一个4字节的10
	int *&&p = (int*)0x0018ff44;
	//int *const& p = (int*)0x0018ff44;

	int a = 10;
	int* p = &a;
	const int*& q = p;
	return 0;
}

#endif
/*
C++的引用   引用和指针的区别？
1.左值引用和右值引用
2.引用的实例
	
定义一个指针变量和一个引用变量，在汇编层面上是没有区别的，都是通过指针来进行的，跟指针是一样的。
定义引用变量  一是必须要可以进行初始化，二是必须可以取地址
引用是更安全的指针。
1.引用是必须初始化的，指针可以不用初始化
2.引用只有一级引用，没有多级引用；指针可以有一级指针，也可以有多级指针
3.定义一个引用变量和一个指针变量，其汇编指令是一模一样的；
  通过引用变量修改所引用变量的值，和通过指针解引用修改指针指向内存的值，其底层指令也是一样的

 右值引用
 1.int &&c = 20;  专门用来引用右值类型，指令上，可以自动产生临时量，然后直接引用临时量，可以通过右值引用c修改临时量内存c=40
 2.右值引用变量本身是一个左值，只能用左值引用来引用它
 3.不能用一个右值引用变量，来引用一个左值

 左值：可以取地址，有名字的，非临时的就是左值
 右值：不能取地址，没有名字的，临时的就是右值。
  
  */

#if 0

int main()
{
	int a = 10;	//左值，它有内存，有名字，值可以修改的
	int& b = a;

	//int& c = 20;	//20是右值：没内存，没名字
	//C++提供了右值引用
	int&& c = 20;
	c = 30;		//可以修改临时量内存

	int& e = c;	//一个右值引用变量，本身就是一个左值

	/*
	int temp=20;
	temp -> d
	*/
	const int& d = 20;
	//d = 20;	//不能修改临时量内存，引用变量作为一个常量，不能作为左值。

	return 0;
}


int main()
{
	int array[5] = {};
	int* p = array;
	//定义一个引用变量，来引用array数组
	int(&q)[5] = array;

	cout << sizeof(array) << endl;	//20
	cout << sizeof(p) << endl;		//4
	cout << sizeof(q) << endl;		//20
	return 0;
}

void swap1(int *a, int *b)
{
	int tmp = *a;
	*a = *b; 
	*b = tmp;
}
void swap(int& a, int& b)
{
	int tmp = a;
	a = b;
	b = tmp;
}
int main()
{
	int a = 10;
	int b = 20;
	//swap(&a, &b);
	swap(a, b);
	cout << "a" << a << "b" << b << endl;


	//int a = 10;

	//int* p = &a;

	//int& b = a;		//引用

	
	return 0;
}


#endif


/*
const和二级指针的结合

常见有3种：

const int **q;	const修饰的是**q   =>	*q可以被赋值，q也可以被赋值(**q不能被赋值)
		
int *const* q;	const修饰的是*q    =>	**q和q都可以被赋值(*q不能被赋值)

int **const q;	const修饰的是q	   =>	**q和*q都可以被赋值(q不能被赋值)


类型转换公式：
int**	<=		const int**			是错误的
const int**		<=		int**		是错误的	


int**	<=	int* const*			是错误的
int* const*		<=	int**		是正确的
const和多级指针结合转换的时候，必须两边都同时有（或者没有）const！！！
 */

#if 0
int main()
{
	int a = 10;
	int* p = &a;
	const int **q = &p;		//const int**  <=  int**   错误

	return 0;

}

#endif
/*
const和一级指针的结合
const和二级(多级)指针的结合

const修饰的量叫做常量  
与普通变量的区别是什么？
C++有两点区别？   1.编译方式不同   2.不能作为左值

const和指针结合  经常出现的问题是？
				1.常量不能再作为左值    《=  直接修改常量的值
				2.不能把常量的地址，泄露给一个普通的指针或者普通的引用变量    《=   可以间接的修改常量的值

const和一级指针的结合  有两种情况
C++的语言规范：const修饰的是离它最近的类型
const int *p; const修饰的是*p	=>	*p不能再被赋值  p=&b p本身可以被赋值	
可以指向任意不同的int类型的内存，但是不能通过指针间接修改指向的内存的值

int const* p;   const修饰的是*p  同上

int *const p;    const修饰的是p的本身   =>   p本身不能再被修改   *p可以被修改
这个指针p现在是常量，不能再指向其他内存，但是可以通过指针解引用修改指向的内存的值

const int *const p;   const修饰的是p本身   =>  p不能被赋值    *p也不能被修改



const如果右边没有指针*的话，const是不参与类型的


总结const和指针的类型转换公式：（从右往左转换）
int*  <=   const int*		是错误的
const int*  <=  int*		是可以的  


*/

#if 0
int main()
{
	//int a = 10;
	//const int* p = &a;
	/const int* p = nullptr;
	int* q = p;	//		int*  <= const int*	  错误 
	//与a没有关系  类型转换就是错误的


	//int* q1 = nullptr;
	//int* const q2 = nullptr;
	//cout << typeid(q1).name() << endl;
	//cout << typeid(q2).name() << endl;
	//const如果右边没有指针*的话，const是不参与类型的

	//int a = 10;
	//int* p1 = &a;
	//const int* p2 = &a;		//const int* <= int* 
	//int* const p3 = &a;		//int *  <= int*
	//int* p4 = p3;			//int*  <=  int*

	//const int a = 10;
	//int* p = &a;		
	//const int* p = &a;	//*p不能被赋值
	//int* const p = &a;	//*p依然可以被赋值

	return 0;
}

#endif

/*
const  指针  引用  在函数中的引用

const 怎么理解？ 
const修饰的变量不能再作为左值！ 初始化完成后，值不能被修改


C和C++在const的区别是什么？
C和C++的编译方式不同，C中，就是当作一个变量来编译生成指令。
在C++中，所有出现const常量名字的地方，都被常量的初始化替换了

在C中	const修饰的量，可以不用初始化  
		不叫常量，叫做常变量
在C++中   必须进行初始化，叫做常数
		  
		  常变量  因为初始值不是立即数，是一个变量
*/






/*
函数重载
1.c++为什么支持函数重载，c语言不支持函数重载
	c++代码产生符号的时候，是由函数名+参数列表类型来组成
	c代码产生函数符号的时候，只由函数名来决定
2.函数重载需要注意什么？
3.c++和c语言代码之间如何互相调用

函数重载
1.一组函数，其中函数名相同，参数列表的个数或者类型不同，那么这一组函数就称作-函数重载。
2.一组函数称的上重载，一定是先处在同一个作用域(同处于一个局部或者全局作用域)中
3.当给参数加上const或者volatile(写多线程程序，解决多线程进程内存可见性)的时候，怎么影响形参类型的。
4.一组函数，函数名相同，参数列表也相同，仅仅是返回值不同，这个不叫重载。

函数重载可以解决多态问题

请你解释一下，什么是多态？
静态(编译时期)的多态：函数重载，模板
动态(运行时期)的多态

什么是函数重载？

c调用c++：  无法直接调用  怎么办？ 把c++源码扩在extern "C"里面
				c在生成符号的时候是按照函数名为基准生成的
c++调用c代码：无法直接调用   怎么办？  把c函数的声明扩在extern "C"里面
				c++在生成符号时，是以函数+符号生成的
*/

//只要是c++编译器，都内置了_cplusplus这个宏名
//由于c++编译器内置了_cplusplus，因此在c++编译时，自动加上extern "C",使生成的C++符号变成C的符号
//在c编译器进行编译时，由于c编译器没有内置这个宏名，因此在编译的时候生成C的符号
//不管是用c编译器还是c++编译器生成，都可以直接给其他的c项目来调用

#if 0
#ifdef  _cplusplus
extern "C" {
#endif
	int sum(int a, int b)
	{
		return a + b;
	}
#ifdef  _cplusplus
}
#endif





extern "C" {
	int sum(int a, int b)
	{
		return a + b;
	}
}

extern "C"
{
	int sum(int a, int b);
}
int main()
{
	int ret = sum(10, 20);
	cout << "ret:" << ret << endl;
	return 0;
}



bool compare(int a, int b)		//compare_int_int 
{
	cout << "compare_int_int" << endl;
	return a > b;
}
bool compare(double a, double b)		//compare_double_double
{
	cout << "compare_double_double" << endl;	
	return a > b;
}
bool compare(const char *a, const char *b)		//compare_char_char
{
	cout << "compare_char_char" << endl;	
	return strcmp(a ,b) > 0;
}
//int data = 10;
int main()
{
	//int data = 20;
	//int a = ::data(全局作用域);

	bool compare(int a, int b);		//函数的声明

	compare(10, 20);
	compare(10.0, 20.0);	//double->int   精度丢失
	compare("aaa", "bbb");	//const char* ->int  无法转成int
	return 0;
}



/*
2、inline函数(内联函数)和普通函数的区别？
		普通函数调用有标准的函数开销，内联函数是在函数编译阶段，在函数的调用点，把函数的代码直接进行展开，节省函数开销
		如果这个函数在短时间内大量调用且这个函数相对简单，那么就把这个函数设置成内联函数。

      内联函数：在编译过程中，就没有函数的调用开销了，在函数的调用点直接把函数的代码进行展开处理
	  内联函数不再生成相应的函数符号

	  inline只是建议编译器把这个函数处理成内联函数
	  但是不是所有的内联函数都会被编译器处理成内联函数，比如：递归

	  debug版本上，inline是不起作用的；inline只有在release版本下才能出现。
*/
inline int sum(int a, int b)
{
	return a + b;
}
int main()
{
	int a = 10;
	int b = 20;

	int ret = a + b;
	//int ret = sum(a, b);   
	//此处有标准的函数调用过程  参数压栈，函数栈帧的开辟和回退过程
	//有函数调用的开销   
	
	cout << "ret:" << ret << endl;
	return 0;
}



/*
1、形参带默认值的函数
   a.给默认值的时候从右向左给。
   b.调用效率的问题
   c.定义处可以给形参默认值，声明也可以给形参默认值
   d.形参给默认值的时候，不管是定义处给还是声明处给，形参默认值只能出现一次
*/
int sum(int a, int b)
{
	return a + b;
}
int main()
{
	int a = 10;
	int b = 20;

	int ret = sum(a, b);
	/*
	mov eax,dword ptr[ebp-8]
	push eax
	mov ecx,dword ptr[ebp-4]
	pusd ecx
	call sum
	*/
	cout << "ret:" << ret << endl;
	return 0;
}
#endif