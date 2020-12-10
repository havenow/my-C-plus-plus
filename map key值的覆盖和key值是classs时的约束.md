# map相同key覆盖问题
```
C++的标准库关联容器map是不允许有key相同的键值对存在的。那么当key已经存在的情况下，我们再次插入相同的key，那么key的value会被覆盖吗？
使用insert()插入元素的方式并不能覆盖掉相同key的值；
而使用[]方式则可以覆盖掉之前的值。

原因：
在map的源码中，insert方法是这样定义的：
调用_M_t.insert_unique(_x)方法，该方法会首先遍历整个集合，判断是否存在相同的key，如果存在则直接返回，放弃插入操作。如果不存在才进行插入。
而[]方式是通过重载[]操作符来实现的，它直接进行插入或覆盖。

所以，不推荐使用[]来判断key是否存在，因为使用操作符[]会向map容器里插入或覆盖。
```

# 在map中，由key查找value时，首先要判断map中是否包含key
```
如果不检查，直接返回map[key]，可能会出现意想不到的行为。如果map包含key没有问题.
如果map不包含key，使用下标有一个危险的副作用，会在map中插入一个key的元素，value取默认值，返回value。也就是说，map[key]不可能返回null。

map提供了两种方式，查看是否包含key，m.count(key)，m.find(key)。
m.count(key)：由于map不包含重复的key，因此m.count(key)取值为0，或者1，表示是否包含。
m.find(key)：返回迭代器，判断是否存在。

//效率差很多。因为需要执行两次查找
1 if(m.count(key)>0)
2 {
3     return m[key];
4 }
5 return null;

//只查找一次
1 iter = m.find(key);
2 if(iter!=m.end())
3 {
4     return iter->second;
5 }
6 return null;

STL中的容器，有泛型算法find(begin，end，target)查找目标，map还提供了一个成员方法find(key)
```

# map的键类型，必须支持<操作符
```
对于map的键类型，唯一的约束是必须支持<操作符，至于是否支持其他的关系或相等运算，则不做要求
如果没有重载<，编译的时候会报错

如果map的Key为内置，则通常已支持<操作，比如map<int>，int类型已经支持<
string可以作为key值是因为string重载了<

cplusplus上面map构造函数demo
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

