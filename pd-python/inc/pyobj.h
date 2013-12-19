#include<m_pd.h>
#include<Python.h>
typedef struct pyobj
{
	t_object	self;
	size_t		icount;
	t_inlet**	inlet;
	size_t		ocount;
	t_outlet**	outlet;
	PyObject*	local;
	PyObject*	global;
}t_pyobj;
void pyobj_setup();
void*pyobj_new(const t_symbol*);
void pyobj_del(t_pyobj const*);
//void pyobj_load(pyobj_t const*,const t_symbol*const);
void pyobj_call(t_pyobj*const,const t_symbol*const,const int,t_atom*const);
void pyobj_exec(t_pyobj*const,const t_symbol*const,const int,t_atom*const);
void pyobj_eval(t_pyobj*const,const t_symbol*const,const int,t_atom*const);
void pyobj_opts(t_pyobj*const,const t_symbol*const,const int,t_atom*const);
void pyobj_load(t_pyobj*const,const t_symbol*const);
void pyobj_dofn(t_pyobj*const,const t_floatarg);
void pyobj_init(t_pyobj*const);
void pyobj_bang(t_pyobj*const);
void pyobj_send(t_outlet*const,PyObject*const);
void pyobj_dump(t_pyobj*const);

PyObject*pd_post(PyObject*const self,PyObject*const args);
PyObject*pd_send(PyObject*const self,PyObject*const args);
PyObject*pd_seta(PyObject*const self,PyObject*const args);
PyObject*pd_geta(PyObject*const self,PyObject*const args);

