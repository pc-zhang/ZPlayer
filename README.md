用100行C++代码实现了音视频解码到播放流程，播放一个抖音视频

[讲解视频戳这里](http://www.365yg.com/item/6525432380486844932/)

**0.线程结构**

![alt](https://photo.tuchong.com/3170996/f/18931663.jpg)

视频播放时要向音频做同步

**1.取视频元信息，并打开音视频解码器**

![alt](https://photo.tuchong.com/3170996/f/18931679.jpg)

**2.打开视频设备（SDL Renderer）**

![alt](https://photo.tuchong.com/3170996/f/18931685.jpg)

**3.打开音频设备（SDL Audio）**

![alt](https://photo.tuchong.com/3170996/f/18931683.jpg)

**4.解复用，解码视频**

![alt](https://photo.tuchong.com/3170996/f/18931686.jpg)

这里应该把视频帧渲染分到另外一个线程，并且渲染的时间要向音频同步，还没有实现

**5.解码音频**

![alt](https://photo.tuchong.com/3170996/f/18931684.jpg)

这里将多通道的音频数据交错到单通道，交给SDL Audio设备去播放
