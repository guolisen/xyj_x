
/*

/d/qujing/pansi/zhuogou	girl7

$N�����


, "name" : 

֩��			����������ճ���ˣ������ǹ�����
				$N˲��֯����һ�Ŵ��������������룬����������Ͷ������
				һ��紵����֩�������Ʈɢ�ˡ�
*/


string _long = @LONG

һֻ�޴��֩�룬ͨ���ɫ�������к�ɫ��ɳ©״ͼ����һ����
�õ���������ӵ�������������ֻʣһ�����ʱ�䡣

LONG;

mapping _prop = ([
	"�ڹѸ�"	: ([
		"ids"		: ({"hei guafu", "guafu", "spider"}),
	])
]);



int do_act(object me, object target)
{
	object hook = new(CMD_HOOK);
	hook->set_listener(_this, "perform")
	stone->set("host", me);


	msv("$N˲��֯����һ�Ŵ��������������룬����������Ͷ������", me);

	
}

