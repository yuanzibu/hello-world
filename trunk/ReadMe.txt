1、bin为软件运行目录，存放exe和dll
	|
	|--ElectricSaw.exe		release版雕刻机主程序exe
	|--DataManager.dll		release版数据管理模块dll
	|--FileReadWrite.dll	release版文件读写模块dll
	|
	|--ElectricSawd.exe		debug版雕刻机主程序exe
	|--DataManagerd.dll		debug版数据管理模块dll
	|--FileReadWrited.dll	debug版文件读写模块dll

	
2、doc为文档目录，存放一刀切算法的各种相关文档
	|
	|--工作计划
	|--软件设计说明书
	|--算法设计图
	|--异形相关文档
	|--月度开会总结文档
	
	
3、include为头文件目录，存放各个模块所使用的头文件
	|
	|--DataManager			数据管理模块头文件
	|--FileReadWrite		文件读写模块头文件
	
	
4、lib为库文件目录，存放各个模块所生成的库文件
	|
	|--DataManager.lib		release版数据管理模块lib
	|--FileReadWrite.lib	release版文件读写模块lib
	|
	|--DataManagerd.lib		debug版数据管理模块lib
	|--FileReadWrited.lib	debug版文件读写模块lib
	

5、src为源代码目录，存放软件各个模块的全部代码
	|
	|--ElectricSaw.sln		VS2010工程文件
	|--ElectricSaw			雕刻机主程序
	|--DataManager			数据管理模块
	|--FileReadWrite		文件读写模块
