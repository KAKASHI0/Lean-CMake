工程的依赖库：

1、网络库：NetLibs
这部分库不提供源码，只有include目录的头文件和lib中的Debug和RelWithDebInfo目录下的连接库。
目前Windows版是静态链接的，Linux版是动态链接

2、boost库
目前的boost库使用了1.39.0版本。这个库是在SVN中已经编译好的。如果要升级等，要进行以下步骤：
	1、将boost目录复制到include目录中
	2、编译好date_time filesystem system thread这四个组件，放到lib目录下(Windows需要编译MultiThreaded版本的)

3、cmake编译的库
这部分库在src中有源码，需要手动进行编译。
目前包括4个库（都是静态链接，不需要额外的dll来运行）：
gtest 1.4.0
lua 5.1.4
luabind 0.9 （luabind/lua_include.hpp做了小修改，将lua.h的位置改到了lua/lua.h）
mysql-connector-c 6.0.2 （工程文件去掉了不相干的工程，并设置了输出位置，
			修复了GCC下不能编译的Bug?）
其中，前3个库整合到了一个工程文件中，而第四个由于比较复杂，暂时没有整合。
Windows：运行cmake.bat，会生成两个工程，Dependencies.sln是前3个工程，
	src/mysql-connector-c-6.0.2是第4个工程。
	两个工程分别编译Debug和RelWithDbgInfo版本的ALL_BUILD工程，
	即可在lib下生成对应版本的库。（INSTALL工程可以把头文件安装到include目录下）
Linux：运行
	./configure
	./build
	即可生成lib下的Debug和RelWithDbgInfo版本的库
	（make install可以把头文件安装到include目录下）
	（./configure里在配置mysql-connector-c 6.0.2时，把生成的配置头文件复制到了include目录下，
	因为原版不支持Out-of-source的Cmake方式）