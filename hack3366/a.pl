#!/usr/bin/perl
use strict;
use warnings;
use LWP;
use HTTP::Request;

my $k10 = $ARGV[0];
my $cookies='pt2gguin=o0383546035; ptcz=4758d0b6fed1a6e45f8d5f84c9e1a39316261b5b62d78326694311d1dcbb7eee; pgv_pvid=2477579949; pgv_flv=10.1 r102; pgv_r_cookie=1111427632361; o_cookie=383546035; mgpcommisnew=1; uin=o0383546035; skey=@RZaA41cic; pgv_info=ssid=s3516389980';
my $score = 999999; #想要的分数,不能太高.
my $user = "用户QQ";
my $pid = "1000044"; #游戏ID号

my $key = substr($k10, 42, 6);
my $k8 = toInt($key);
my $k4 = fromInt($k8, 35);
my $k13 = length $k4;
my $k3 = int(toInt(substr($key, length($key)-1), 36) % $k13);
my $k6 = fromInt($score, 36);
my $k12 = substr($k4, 0, $k3);
my $k7 =  substr($k4, $k3);
my $k5 = $k3 + 10;
my $k11 = $k5 + length($k6);
my @r = (fromInt($k5, 36),
	$k12,
	$k6,
	$k7,
	fromInt($k11, 36),
	$k10);

my $fkey = join "", @r;





sub toInt {
	my @value = split('', shift);
	my %base;
	@base{ ('0'..'9', 'a'..'z') } = ('0'..'35');

	my $r = 0;
	foreach (@value) {
		$r *= 36;
		$r += $base{$_};
	}
	return $r;
}

sub fromInt {
	my $v = shift;
	my $b = shift;

	my %code;
	@code{ ('0'..$b) } = ('0'..'9', 'a'..'z');

	my @value;
	my $t;
	while($v/$b != 0){
		$t = int($v%$b);
		unshift @value, $code{$t};
		$v = int($v/$b);
	}
	return join "", @value;

}

my $url = "http://fcg.3366.com/fcg-bin/qz/play";

my $ua = LWP::UserAgent->new();

my $request = HTTP::Request->new(
	POST=>$url,
	[
		"User-Agent"=>'Mozilla/5.0(X11; U; Linux i686; en-US',
		"Accept"=>"text/html,*/*",
		"Cookie"=>$cookies,
		"Referer"=>"http://img.3366.com/fileupload/flash/com/comm.swf",
	]
);
my $k = join "", ("key=", $fkey,
	"&bookId=0&pkMode=1&submit=true&uin=$user&score=$score&act=set&pid=$pid");
print "\$k: $k\n";
$request->content($k);

$ua->request($request, "result.html");
