

//是否可以保存
int can_save(object ob)
{	
	int n = ob->query_amount();	
	if(!n) {
		object ob1 = new(base_name(ob));
		int ret = 0;
		if(ob1) {
			ret = !sizeof(all_inventory(ob1))
				&& var_equal(ob1->query_entire_dbase(), ob->query_entire_dbase())
				&& var_equal(ob1->query_entire_temp_dbase(), ob->query_entire_temp_dbase());
			destruct(ob1);
		}
		return ret;
	}
	return 1;
}

