
#ifndef SLANG_SIMPLIFY_H
#define SLANG_SIMPLIFY_H


extern GLint
_slang_lookup_constant(const char *name);


extern void
_slang_simplify(slang_operation *oper,
		const slang_name_space * space,
		slang_atom_pool * atoms);


extern GLboolean
_slang_adapt_call(slang_operation *callOper, const slang_function *fun,
		  const slang_name_space * space,
		  slang_atom_pool * atoms, slang_info_log *log);


#endif /* SLANG_SIMPLIFY_H */

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
