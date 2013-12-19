#include<pyobj.h>
void pyobj_call(t_pyobj*const ins,const t_symbol*const s,const int argc,t_atom*const argv)
{
	register unsigned int k,K;
	PyObject*args=PyTuple_New(argc);
	for(k=0,K=argc;k<K;++k)
	switch(argv[k].a_type)
	{
	case A_FLOAT:
		PyTuple_SetItem(args,k,PyFloat_FromDouble(atom_getfloat(argv+k)));
		break;
	case A_SYMBOL:
		PyTuple_SetItem(args,k,PyString_FromString(atom_getsymbol(argv+k)->s_name));
		break;
	default:
		PyTuple_SetItem(args,k,Py_None);
		break;
	}
	PyObject*func=PyRun_StringFlags(s->s_name,Py_eval_input,ins->global,ins->local,0);
	if(func)
	{
		pyobj_send(*ins->outlet,PyObject_Call(func,args,0));
		Py_DECREF(func);
	}
	Py_DECREF(args);
}
void pyobj_bang(t_pyobj*const ins)
{
	PyObject*args=Py_None;
	pyobj_send(*ins->outlet,PyObject_Call(PyRun_StringFlags("bang",Py_eval_input,ins->global,ins->local,0),args,0));
	pyobj_dump(ins);
}
void pyobj_dofn(t_pyobj*const ins,const t_floatarg f)
{
	PyObject*args=PyTuple_New(1);
	PyTuple_SetItem(args,0,PyFloat_FromDouble(f));
	pyobj_send(*ins->outlet,PyObject_Call(PyRun_StringFlags("number",Py_eval_input,ins->global,ins->local,0),args,0));
	pyobj_dump(ins);
}
void pyobj_load(t_pyobj*const ins,const t_symbol*const s)
{
	if(strlen(s->s_name))
	{
		FILE*fp=fopen(s->s_name,"r");
		if(fp)
		{
			PyRun_FileExFlags(fp,s->s_name,Py_file_input,ins->global,ins->local,0,0);
			fclose(fp);
		}
		else post("File %s: not found",s->s_name);
	}
}
void pyobj_exec(t_pyobj*const ins,const t_symbol*const s,const int argc,t_atom*const argv)
{
	register int k,K;
	char*	src=0;
	int	sum=0;
	for(k=0,K=argc;k<K;++k)
	{
		switch(argv[k].a_type)
		{
		case A_SYMBOL:
			{
				int pch=strlen(atom_getsymbol(argv+k)->s_name);
				src=realloc(src,sum+pch+1);
				memcpy(src+sum,atom_getsymbol(argv+k)->s_name,pch);
				src[sum+pch]=' ';
				sum+=pch+1;
			}
			break;
		case A_FLOAT:
			{
				char	buff[64];
				sprintf(buff,"%lf",atom_getfloat(argv+k));
				int pch=strlen(buff);
				src=realloc(src,sum+pch+1);
				memcpy(src+sum,buff,pch);
				src[sum+pch]=' ';
				sum+=pch+1;
			}
			break;
		default:
			break;
		}
	}
	src[sum-1]=0;
	PyRun_StringFlags(src,Py_file_input,ins->global,ins->local,0);
	pyobj_dump(ins);
	free(src);
}
void pyobj_eval(t_pyobj*const ins,const t_symbol*const s,const int argc,t_atom*const argv)
{
	register int k,K;
	char*	src=0;
	int	sum=0;
	for(k=0,K=argc;k<K;++k)
	{
		switch(argv[k].a_type)
		{
		case A_SYMBOL:
			{
				int pch=strlen(atom_getsymbol(argv+k)->s_name);
				src=realloc(src,sum+pch+1);
				memcpy(src+sum,atom_getsymbol(argv+k)->s_name,pch);
				src[sum+pch]=' ';
				sum+=pch+1;
			}
			break;
		case A_FLOAT:
			{
				char	buff[64];
				sprintf(buff,"%lf",atom_getfloat(argv+k));
				int pch=strlen(buff);
				src=realloc(src,sum+pch+1);
				memcpy(src+sum,buff,pch);
				src[sum+pch]=' ';
				sum+=pch+1;
			}
			break;
		default:
			break;
		}
	}
	src[sum-1]=0;
	pyobj_send(*ins->outlet,PyRun_StringFlags(src,Py_eval_input,ins->global,ins->local,0));
	pyobj_dump(ins);
	free(src);
}
