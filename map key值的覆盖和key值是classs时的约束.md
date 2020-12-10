# map��ͬkey��������
```
C++�ı�׼���������map�ǲ�������key��ͬ�ļ�ֵ�Դ��ڵġ���ô��key�Ѿ����ڵ�����£������ٴβ�����ͬ��key����ôkey��value�ᱻ������
ʹ��insert()����Ԫ�صķ�ʽ�����ܸ��ǵ���ͬkey��ֵ��
��ʹ��[]��ʽ����Ը��ǵ�֮ǰ��ֵ��

ԭ��
��map��Դ���У�insert��������������ģ�
����_M_t.insert_unique(_x)�������÷��������ȱ����������ϣ��ж��Ƿ������ͬ��key�����������ֱ�ӷ��أ����������������������ڲŽ��в��롣
��[]��ʽ��ͨ������[]��������ʵ�ֵģ���ֱ�ӽ��в���򸲸ǡ�

���ԣ����Ƽ�ʹ��[]���ж�key�Ƿ���ڣ���Ϊʹ�ò�����[]����map���������򸲸ǡ�
```

# ��map�У���key����valueʱ������Ҫ�ж�map���Ƿ����key
```
�������飬ֱ�ӷ���map[key]�����ܻ�������벻������Ϊ�����map����keyû������.
���map������key��ʹ���±���һ��Σ�յĸ����ã�����map�в���һ��key��Ԫ�أ�valueȡĬ��ֵ������value��Ҳ����˵��map[key]�����ܷ���null��

map�ṩ�����ַ�ʽ���鿴�Ƿ����key��m.count(key)��m.find(key)��
m.count(key)������map�������ظ���key�����m.count(key)ȡֵΪ0������1����ʾ�Ƿ������
m.find(key)�����ص��������ж��Ƿ���ڡ�

//Ч�ʲ�ܶࡣ��Ϊ��Ҫִ�����β���
1 if(m.count(key)>0)
2 {
3     return m[key];
4 }
5 return null;

//ֻ����һ��
1 iter = m.find(key);
2 if(iter!=m.end())
3 {
4     return iter->second;
5 }
6 return null;

STL�е��������з����㷨find(begin��end��target)����Ŀ�꣬map���ṩ��һ����Ա����find(key)
```

# map�ļ����ͣ�����֧��<������
```
����map�ļ����ͣ�Ψһ��Լ���Ǳ���֧��<�������������Ƿ�֧�������Ĺ�ϵ��������㣬����Ҫ��
���û������<�������ʱ��ᱨ��

���map��KeyΪ���ã���ͨ����֧��<����������map<int>��int�����Ѿ�֧��<
string������Ϊkeyֵ����Ϊstring������<

cplusplus����map���캯��demo
// constructing maps
#include <iostream>
#include <map>

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs<rhs;}
};

int main ()
{
  std::map<char,int> first;

  first['a']=10;
  first['b']=30;
  first['c']=50;
  first['d']=70;

  std::map<char,int> second (first.begin(),first.end());

  std::map<char,int> third (second);

  std::map<char,int,classcomp> fourth;                 // class as Compare

  bool(*fn_pt)(char,char) = fncomp;
  std::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare

  return 0;
}


```

