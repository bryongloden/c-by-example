#define stringify(x) #x

#define HASH_INT_LEN(s)			((sizeof(s)/sizeof(s[0])) - 1)
#define HASH_INT_1(s,i,x)		(x*65599u+(unsigned char)s[(i)<HASH_INT_LEN(s)?HASH_INT_LEN(s)-1-(i):HASH_INT_LEN(s)])
#define HASH_INT_4(s,i,x)		HASH_INT_1(s,i,HASH_INT_1(s,i+1,HASH_INT_1(s,i+2,HASH_INT_1(s,i+3,x))))
#define HASH_INT_16(s,i,x)		HASH_INT_4(s,i,HASH_INT_4(s,i+4,HASH_INT_4(s,i+8,HASH_INT_4(s,i+12,x))))
#define HASH_INT_64(s,i,x)		HASH_INT_16(s,i,HASH_INT_16(s,i+16,HASH_INT_16(s,i+32,HASH_INT_16(s,i+48,x))))

#define HASH_S64(s)	((unsigned int)(HASH_INT_64(s,0,0)^(HASH_INT_64(s,0,0)>>16)))	///< Hash value from string with a max length of 64 bytes.
#define HASH_S16(s)	((unsigned int)(HASH_INT_16(s,0,0)^(HASH_INT_16(s,0,0)>>16)))	///< Hash value from string with a max length of 16 bytes.

#define DECL_STRUCT_FINGERPRINT \
	struct { \
		uint32_t id; \
		const char *name; \
	} __meta;

#define DECL_STRUCT_MEMBER(type, name) \
	type name;

#define DEF_STRUCT(sname, body) \
	static const uint32_t sname##__id = HASH_S64(stringify(sname)); \
	static const char *sname##__name = stringify(sname); \
	struct sname { \
		DECL_STRUCT_FINGERPRINT \
		body \
	};

#define decl_var(sname, x) struct sname x; x.__meta.id = sname##__id; x.__meta.name = sname##__name;
#define decl_get_id(x) x.__meta.id
#define decl_get_name(x) x.__meta.name