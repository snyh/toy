不记得是几年前暑假尝试写的一个LED走字屏相关的程序.
不过只刚刚起步就没做了, 当时能力有限吧, 不过如果好好做也应该能完成的.

那时候专业是嵌入式接触这方面的东西比较多, 本打算是做一个linux下的走字屏,
先写一个字模软件生成数据, 然后通过界面进行展示并做一些效果. 最后通过
和单片机上编写的程序进行通讯进行数据烧录.

现在看来字幕生成是完成了单独放在draw_words这个小toy里面在, 展示界面也做
了一点只是在换字的时候会有问题, 当时对数据结构算法什么的一点都不了解所以
做那一块出了问题.  

烧录程序和效果制作都完全没有开始,

现在看来其实都挺简单的, 烧录用asio的serial可以做到跨平台不用限定死在linux下
只是单片机那边好久没碰过了但熟悉一下也能很快恢复起来的.

单片机方面去年打算做一个用遥控器控制的俄罗斯方块游戏, 在proteus里面已经完成
一半了可以绘制方块消除方块, 不过当时仿真红外的时候出了麻烦, 因为是仿真而且仿真
软件还是通过wine模拟跑的>_<, 加上两边都不稳定所以总调试不出来, 如果有一边是
用实物进行调式就很简单了. 只是觉得那个老师有点不正常不想过多接触就没去实验室
做。

虽然学了这么多年嵌入式，但自己似乎还是没天赋，在这方面没做出过任何完整的
东西来。唯一一次自己满意的是有年实训,内容是根据给的protel文件进行学习然后
在做好的板子上进行焊接. 不过我当时没有看那个文件, 直接通过需要完成的功能(好像
红绿灯)在proteus里面进行仿真和PCB图的排线, 可惜当时根本就不整理文件东西都是
乱丢的.
