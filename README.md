Dwylkz's Interface Framework

Type +-Inheritance,	[ Dependencies... ] and { interfaces... }

	Object
	\
	 +-LinkedList [ ListNode, Value ] { Container }
	 | \
	 |	+-Queue [ LinkedList ] { DoublyQueue }
	 |
	 +-ListNode [ Vector, Value ] { Node }
	 | \
	 |	+-BSTNode [ ListNode, Vector, Value ] { Node, BSTNode }
	 |
	 +-Pair { PairType }
	 |
	 +-Value { BasicType }
	 |
	 +-Vector [ Value ]	{ Container }
	 |
	 +-SBT [ BSTNode ] { Container }

General Naming Rule:

	Obey the Google C/C++ programming Style

INTERFACE.i Format:

	#ifndef INTERFACE_I_
	#define INTERFACE_I_

	interface {
		Method SetM(METHOD);
		...
	} INTERFACE##I;
	SetT(RETURN_TYPE, METHOD, PARA_TYPE PARAMETER...);
	...

	#endif // INTERFACE_I_

TYPE.h Format:

	#ifndef TYPE_H_
	#define TYPEE_H_

	#include "Info.h"
	#include "INTERFACE.i"
	...

	// One Type has only one super type.
	#include "SUPER_TYPE.h"

	Define(TYPE##D) {
		Info _;
		INTERFACE##I INTERFACE##_;
		...
	};
	Define(TYPE) {
		struct SUPER_TYPE##_;
		MEMBER_TYPE MEMBER##_;
		...
	};
	extern Type TYPE;

	Func(RETURN_TYPE, TYPE##METHOD, PARA_TYPE PARAMETER...);
	...

	#endif // TYPE_H_

TYPE.c Format:

	#include "TYPE.h"

	#include "DEPENDENCY.h"
	...

	Func(RETURN_TYPE, TYPE##METHOD, PARA_TYPE PARAMETER...)
	{
		...
	}
	...

	struct TYPED _##TYPE = {
		// Info
		{
			"TYPE",
			sizeof(struct TYPE),
			sizeof(struct TYPE##D),
			// Basic
			{
				PutM(TYPE, METHOD),
			}
		},
		// INTERFACE
		{
			PutM(TYPE, METHOD),
			...
		},
		...
	};
	Type TYPE = &_##TYPE;
