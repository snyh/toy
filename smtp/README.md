寒假实习无聊写的一个SMTP发邮件的小程序,
功能很不完善, 当时刚刚接触ASIO.
可以实现gmail邮件的发送也就是支持SSL.

主要是一个发送代理构造函数如下
UserAgent(std::string smtp_host, std::string pop_host,
		  std::string user, std::string password,
		  std::string pop_port="110", std::string smtp_port="25", 
		  bool tls=false);
只有三组函数分别用来发送邮件获取邮件和获取邮件列表
void async_sendmail(Mail& m, SendHandler  handle);
std::string sendmail(Mail& m);

void async_listmail(ListHandler handler);
void listMail(MailList& l);

void async_fetchmail(int n, FetchHandler);
void fetchmail(int n, Mail& m);
和一个Mail结构,构造函数如下
Mail(std::string from, 
	 std::string tos, 
	 std::string subject="",
	 std::string data="");

以下是测试内容, 使用QQ邮箱和Gmail邮箱, 敏感信息我稍微处理了下

end
Send:EHLO 127.0.0.1

Send:USER 1399611909@qq.com

250 8BITMIMERESSLAINom
Send:AUTH LOGIN

Recive:+OK
Send:PASS 密码

Recive:334 VXNlcm5hbWU6
Send:密码的Base64编码

Recive:+OK
Send:STAT

Recive:334 UGFzc3dvcmQ6
Send:eGlhYmluMzIx

Recive:+OK 2 3662
Num: 2
Send:TOP 1 0

Recive:235 Authentication successful
Send:MAIL FROM:<1399611909@qq.com>

Recive:250 Ok
Send:RCPT TO:<snyh@snyh.org>

Recive:250 Ok
Send:DATA

.his is a multi-part message in MIME format.F@qq.com>76E5DD"
Send:TOP 2 0

Recive:354 End data with <CR><LF>.<CR><LF>
Send:From:1399611909@qq.com
To:snyh@snyh.org
Subject:test_title
MIME-Version: 1.0

data:test
.

Recive:250 Ok: queued as 
250 Ok: queued as 
test start
Received-SPF: pass (google.com: domain of snyh1010@gmail.com designates 10.182.1Authentication-Results: mr.google.com; spf=pass (google.com: domain of snyh1010@gmail.com designates 10.182.159.105 as permitted sender) smtp.mail=snyh1010@gmai        by 10.182.159.105 with SMTP id xb9mr10064332obb.63.1331049403868 (num_ho.xxxxxxxxxxsnyh.org010@gmail.com>0800 (PST).google.com>9.2012.03.06.07.56.37Z
Send:QUIT
Send:EHLO 127.0.0.1

250 ENHANCEDSTATUSCODESAUTH your service, [58.55.77.198]
Send:AUTH LOGIN

Recive:334 VXNlcm5hbWU6
Send: 密码的base64编码

Recive:334 UGFzc3dvcmQ6
Send:eGlhYmluYGBg

Recive:235 2.7.0 Accepted
Send:MAIL FROM:<snyh1010>

Recive:250 2.1.0 OK f8sm793600oec.9
Send:RCPT TO:<1399611909@qq.com>

Recive:250 2.1.5 OK f8sm793600oec.9
Send:DATA

Recive:354  Go ahead f8sm793600oec.9
Send:From:snyh1010@gmail.com
To:1399611909@qq.com
Subject:test_title
MIME-Version: 1.0

data:test
.
