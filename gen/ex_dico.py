import dic
d = dic.Dico()
ret = dic.Dic_init(d, "../dic/ods8.dico")
if not ret:
    print(dic.isMot(d, "papa"))
    print(dic.isMot(d, "pipi"))
    print(dic.isMot(d, "popo"))
    print(dic.isMot(d, "megotes"))
else:
    print("Error:" , ret)
