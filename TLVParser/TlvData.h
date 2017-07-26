#define TLV_MAX_LENVALUE 490
#define TLV_MAX_OBJECT 50
typedef struct TLV
{
	unsigned long	Tag;
	unsigned long 	Len;
	unsigned char	Value[TLV_MAX_LENVALUE];
}TLV, *LPTLV;

typedef struct TLVSET
{
	TLV Object[TLV_MAX_OBJECT];
	unsigned char   CountPaesedObject;

}TLVSET, *LPTLVSET;

