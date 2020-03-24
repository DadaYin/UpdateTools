# UpdateTools
2020-03-18

1.Common文件夹主要是数据结构定义以及util文件

2.GenParseUpdateJson主要是生成json文件,主要是给服务端生成json文件.指定url地址、版本号以及指定文件目录，即可自动生成.指定文件目录中建议只放必要的文件。

3.UpdateClient主要是升级客户端,通过http将文件下载到本地,校验成功后覆盖到本地目录中.

4.目前只完成json生成部分,客户端下载部分后续抽空弄完成

2020-03-24

运行生成update.json以及客户端都需要复制对应的ini文件

配置文件参数介绍
./config/basic.ini

HttpRootUrl:文件共享url根地址 打开后会有一个update.json文件以及其他必要的文件
MainVersion:主版本号，如果客户端的主版本号与该版本一致，则不进行更新
UpdateDir:文件共享url根地址的物理路径


./config/clientbasic.ini

HttpRootUrl:件共享url根地址 打开后会有一个update.json文件以及其他必要的文件
UpdateDir:需要更新的目录，即正常软件运行目录
TmpUpdateDir:临时下载目录，存放临时下载的文件

使用需配合文件共享服务一起使用
使用需配合文件共享服务一起使用
使用需配合文件共享服务一起使用

重要的事情说3遍
