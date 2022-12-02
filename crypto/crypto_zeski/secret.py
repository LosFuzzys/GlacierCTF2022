flag = b"glacierctf{Th0s3_p4r4m3t3r5_d0nt_l00k_r1ght}"

a = 9267041722223952734748859456602204786592847214552930801625166915140780187538406621175499729057485437691146740375548781989128623066030901688445528104431261
b = 78503358913195129958234189405296173859478493550200997712187362653066465351619230391006386829509519498953154463484429774550025522052914297323198781490566423
m = 727493902383300887565749651392545018195857798383118478781874302989188068946448963613837789599846967397842729645090681213144478081662609469035172950348146276386504171014170192032689352779418699613478557741603478156836239732471390411270369904518926646739423730306838741654020425537473477657324406029655158149403

def roll_faster(x, y):
    if y == 0: return x
    return (int(pow(a, y, m))*x + b) % m