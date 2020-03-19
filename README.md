# UpdateTools
2020-03-18

1.Common文件夹主要是数据结构定义以及util文件

2.GenParseUpdateJson主要是生成json文件,主要是给服务端生成json文件.指定url地址、版本号以及指定文件目录，即可自动生成.指定文件目录中建议只放必要的文件。

3.UpdateClient主要是升级客户端,通过http将文件下载到本地,校验成功后覆盖到本地目录中.

4.目前只完成json生成部分,客户端下载部分后续抽空弄完成
