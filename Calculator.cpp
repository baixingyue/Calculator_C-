#include<iostream>
using namespace std;
class opnd//操作数栈
{
	public:
		opnd();
		double pop();
		void push(double temp);
	private:
		double num[1000];
		int count;
};
opnd::opnd()//操作数栈构造函数
{
	count=0;
}
double opnd::pop()//操作数栈出栈函数
{
	double temp;
	if(count==0)
	{
		cout<<"\n\n操作数栈下溢。\n运算符的非法使用。"<<endl;
		exit(-1);
		return 0;
	}
	else
	{
		temp=num[count-1];
		count--;
		cout<<"操作数:\t"  <<temp  <<"出栈成功。"<<endl;
		return temp;
	}
}
void opnd::push(double temp)//操作数栈入栈函数
{
	if(count==999)
	{
		cout<<"       操作数栈上溢。"<<endl;
		exit(-1);
	}
	else
	{
		num[count]=temp;
		count++;
		cout<<"操作数:\t" <<temp <<"入栈成功。"<<endl;
	}
}

class optr//操作符栈
{
	public:
		optr(char exp[100]);
		char pop();
		void push(char temp);
		void work();
		int value1(char temp);
		int value2(char temp);
		double change(double x, double y, char z);
		opnd mynumber;
	private:
		char theta1[100];
		char expression[100];
		char *ptheta2;
	    char *ptop;
};
optr::optr(char exp[100])
{
	theta1[0]='#';
	ptop=&theta1[0];
	ptheta2=&expression[0];
	int left=0;
	int right=0;

	for(int i=0; i<100; i++)
	{
		if(exp[i]=='(')
			left++;
		if(exp[i]==')')
			right++;
	}
	if(left==right)
	{
		for(i=0; i<100; i++)
			expression[i]=exp[i];
	}
	else
	{
		cout<<"左右括号不匹配。\n";
		exit(-1);
	}
}
char optr::pop()
{
	if(*ptop=='#')
	{
		cout<<"已达操作符栈底。\n";
		exit(-1);
		return '0';
	}
	else
	{
		char temp;
		temp=*ptop;
		ptop--;
		cout<<"操作符:\t" <<temp <<"出栈成功。\n";
		return temp;
	}
}
void optr::push(char temp)
{
	if(ptop==&theta1[99])
	{
		cout<<"       操作符栈上溢\n";
		exit(-1);
	}
	else
	{
		ptop++;
		*ptop=temp;
		cout<<"操作符:\t" <<temp <<"入栈成功。\n";
	}
}

int optr::value1(char temp)
{
	if(temp=='+')
		return 3;
	else if(temp=='-')
		return 3;
	else if(temp=='*')
		return 5;
	else if(temp=='/')
		return 5;
	else if(temp=='(')
		return 1;
	else if(temp==')')
		return 6;
	else if(temp=='#')
		return 0;
	else
		return 0;
}

int optr::value2(char temp)
{
	if(temp=='+')
		return 2;
	else if(temp=='-')
		return 2;
	else if(temp=='*')
		return 4;
	else if(temp=='/')
		return 4;
	else if(temp=='(')
		return 6;
	else if(temp==')')
		return 1;
	else if(temp=='#')
		return 0;
	else
		return 0;
}

double optr::change(double x, double y, char z)
{
	if(z=='+')
		return (x+y);
	else if(z=='-')
		return (x-y);
	else if(z=='*')
		return (x*y);
	else if(z=='/')
	{
		if(y==0)
		{
			cout<<"\n\n除数不能为零。\n\n";
			exit(-1);
			return x;
		}
		else
			return (x/y);
	}
	else
	{
		cout<<"错误的操作符!\n";
		exit(-1);
		return 0;
	}
}

void optr::work()
{
	while(!(((*ptop)=='#')&&((*ptheta2)=='#')))
	{
			if((*ptheta2>='0')&&(*ptheta2<='9'))
			{
		    	int i=0, j=0, k=1, sum=0;
				bool dou=false;
			    char sumoppo[10];
				char dousumoppo[10];
				double dousum=0, douk=0.1;
     			while(((*ptheta2>='0')&&(*ptheta2<='9'))||((*ptheta2!='+')&&(*ptheta2!='-')&&(*ptheta2!='*')&&(*ptheta2!='/')&&(*ptheta2!='(')&&(*ptheta2!=')')&&(*ptheta2!='#')))
				{
					if(*ptheta2=='.')
						dou=true;

					if((*ptheta2!='.')&&(dou==false))
					{
		         		if((*ptheta2>='0')&&(*ptheta2<='9'))
						{
		     	    		sumoppo[i]=*ptheta2;
			        		ptheta2++;
			        		i++;
						}
			        	else
						{
				     		cout<<"剔除非法字符: "<<*ptheta2<<"\n";
			         		ptheta2++;
						}
					}
					else if((*ptheta2=='.')||(dou==true))
					{
						if(*ptheta2=='.')
							*ptheta2++;

				    	if((*ptheta2>='0')&&(*ptheta2<='9'))
						{
		     	    		dousumoppo[j]=*ptheta2;
			        		ptheta2++;
			        		j++;
						}
			        	else
						{
				     		cout<<"剔除非法字符: "<<*ptheta2<<"\n";
			         		ptheta2++;
						}
					}
					else
					{
					}
				}
		    	while(i>0)
				{
				    sum=sum+k*((int)(sumoppo[i-1])-(int)('0'));
			    	k=k*10;
			    	i--;
				}
				k=0;//整型k控制从0开始的存小数的char型数组，douk为权
				while(k<j)
				{
				    dousum=dousum+douk*((double)((int)(dousumoppo[k]))-(double)((int)('0')));
			    	douk=douk/10;
			    	k++;
				}
		    	mynumber.push(sum+dousum);
			}
	    	else if((*ptheta2=='+')||(*ptheta2=='-')||(*ptheta2=='*')||(*ptheta2=='/')||(*ptheta2=='(')||(*ptheta2==')')||(*ptheta2=='#'))
			{
		    	if(value2(*ptheta2)>value1(*ptop))
				{
		 	    	push(*ptheta2);
			    	ptheta2++;
				}
		    	else if((value2(*ptheta2)==value1(*ptop))&&((*ptheta2!='#')&&(*ptop!='#')))
				{
		     		char voi=pop();
		     		ptheta2++;
				}
		    	else
				{
			    	cout<<"\n";

			    	char t_ope;
			    	t_ope=pop();

			    	double s, a, b;
			    	b=mynumber.pop();
			    	a=mynumber.pop();
			    	s=change(a,b,t_ope);
					mynumber.push(s);

			    	cout<<"\n";
				}
			}
	    	else
			{ 
		    	cout<<"剔除非法字符: "<<*ptheta2<<"\n";
		    	ptheta2++;
			}
		
	}
	cout<<"\n计算结果为: "<<mynumber.pop()<<" 。\n";
}


int main()
{   cout<<"********************************欢迎使用计算器*********************************"<<endl;
	cout<<"                         请输入一个表达式，并以#号结束:"<<endl;
	char original[100];
	for(int i=0; i<100; i++)
	{
		cin>>original[i];
		if(original[i]=='#')
		{
			original[i+1]='\0';
			break;
		}
	}
	optr all(original);
	all.work();
	return 0;
}
