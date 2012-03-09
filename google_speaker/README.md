脚本可以单独使用,或者配合其他工具使用比如stardict
建立下载WyabdcRealPeopleTTS真人发音, 可以优秀使用真人发音如果没有找到
则通过google下载发音文件,然后存储在本地.

使用方式
1 修改脚本的参数 $speaker, $dir两个参数, 脚本内有解释作用.

如果需要配合stardict则继续

2 修改stardict的Sound选项,
  勾选Enable TTS program
  在Command line 处改为"google_speak %s &"
	google_speak需要能在$PATH中找到, %s前一定记得空格.
	
	如果无法发音, 请使用命令行启动stardict然后进行发音查看哪里出错.



