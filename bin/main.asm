
./bin/main.out:     file format elf64-x86-64


Disassembly of section .init:

0000000000401000 <_init>:
  401000:	f3 0f 1e fa          	endbr64 
  401004:	48 83 ec 08          	sub    rsp,0x8
  401008:	48 8b 05 e9 7f 16 00 	mov    rax,QWORD PTR [rip+0x167fe9]        # 568ff8 <__gmon_start__>
  40100f:	48 85 c0             	test   rax,rax
  401012:	74 02                	je     401016 <_init+0x16>
  401014:	ff d0                	call   rax
  401016:	48 83 c4 08          	add    rsp,0x8
  40101a:	c3                   	ret    

Disassembly of section .plt:

0000000000401020 <.plt>:
  401020:	ff 35 e2 7f 16 00    	push   QWORD PTR [rip+0x167fe2]        # 569008 <_GLOBAL_OFFSET_TABLE_+0x8>
  401026:	ff 25 e4 7f 16 00    	jmp    QWORD PTR [rip+0x167fe4]        # 569010 <_GLOBAL_OFFSET_TABLE_+0x10>
  40102c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]

0000000000401030 <std::ostream::put(char)@plt>:
  401030:	ff 25 e2 7f 16 00    	jmp    QWORD PTR [rip+0x167fe2]        # 569018 <std::ostream::put(char)@GLIBCXX_3.4>
  401036:	68 00 00 00 00       	push   0x0
  40103b:	e9 e0 ff ff ff       	jmp    401020 <.plt>

0000000000401040 <std::ios_base::sync_with_stdio(bool)@plt>:
  401040:	ff 25 da 7f 16 00    	jmp    QWORD PTR [rip+0x167fda]        # 569020 <std::ios_base::sync_with_stdio(bool)@GLIBCXX_3.4>
  401046:	68 01 00 00 00       	push   0x1
  40104b:	e9 d0 ff ff ff       	jmp    401020 <.plt>

0000000000401050 <__assert_fail@plt>:
  401050:	ff 25 d2 7f 16 00    	jmp    QWORD PTR [rip+0x167fd2]        # 569028 <__assert_fail@GLIBC_2.2.5>
  401056:	68 02 00 00 00       	push   0x2
  40105b:	e9 c0 ff ff ff       	jmp    401020 <.plt>

0000000000401060 <std::ostream& std::ostream::_M_insert<unsigned long>(unsigned long)@plt>:
  401060:	ff 25 ca 7f 16 00    	jmp    QWORD PTR [rip+0x167fca]        # 569030 <std::ostream& std::ostream::_M_insert<unsigned long>(unsigned long)@GLIBCXX_3.4.9>
  401066:	68 03 00 00 00       	push   0x3
  40106b:	e9 b0 ff ff ff       	jmp    401020 <.plt>

0000000000401070 <std::ostream::flush()@plt>:
  401070:	ff 25 c2 7f 16 00    	jmp    QWORD PTR [rip+0x167fc2]        # 569038 <std::ostream::flush()@GLIBCXX_3.4>
  401076:	68 04 00 00 00       	push   0x4
  40107b:	e9 a0 ff ff ff       	jmp    401020 <.plt>

0000000000401080 <__cxa_atexit@plt>:
  401080:	ff 25 ba 7f 16 00    	jmp    QWORD PTR [rip+0x167fba]        # 569040 <__cxa_atexit@GLIBC_2.2.5>
  401086:	68 05 00 00 00       	push   0x5
  40108b:	e9 90 ff ff ff       	jmp    401020 <.plt>

0000000000401090 <std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)@plt>:
  401090:	ff 25 b2 7f 16 00    	jmp    QWORD PTR [rip+0x167fb2]        # 569048 <std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)@GLIBCXX_3.4.9>
  401096:	68 06 00 00 00       	push   0x6
  40109b:	e9 80 ff ff ff       	jmp    401020 <.plt>

00000000004010a0 <std::ctype<char>::_M_widen_init() const@plt>:
  4010a0:	ff 25 aa 7f 16 00    	jmp    QWORD PTR [rip+0x167faa]        # 569050 <std::ctype<char>::_M_widen_init() const@GLIBCXX_3.4.11>
  4010a6:	68 07 00 00 00       	push   0x7
  4010ab:	e9 70 ff ff ff       	jmp    401020 <.plt>

00000000004010b0 <std::__throw_bad_cast()@plt>:
  4010b0:	ff 25 a2 7f 16 00    	jmp    QWORD PTR [rip+0x167fa2]        # 569058 <std::__throw_bad_cast()@GLIBCXX_3.4>
  4010b6:	68 08 00 00 00       	push   0x8
  4010bb:	e9 60 ff ff ff       	jmp    401020 <.plt>

00000000004010c0 <std::ostream::write(char const*, long)@plt>:
  4010c0:	ff 25 9a 7f 16 00    	jmp    QWORD PTR [rip+0x167f9a]        # 569060 <std::ostream::write(char const*, long)@GLIBCXX_3.4>
  4010c6:	68 09 00 00 00       	push   0x9
  4010cb:	e9 50 ff ff ff       	jmp    401020 <.plt>

00000000004010d0 <std::ios_base::Init::Init()@plt>:
  4010d0:	ff 25 92 7f 16 00    	jmp    QWORD PTR [rip+0x167f92]        # 569068 <std::ios_base::Init::Init()@GLIBCXX_3.4>
  4010d6:	68 0a 00 00 00       	push   0xa
  4010db:	e9 40 ff ff ff       	jmp    401020 <.plt>

00000000004010e0 <std::ios_base::Init::~Init()@plt>:
  4010e0:	ff 25 8a 7f 16 00    	jmp    QWORD PTR [rip+0x167f8a]        # 569070 <std::ios_base::Init::~Init()@GLIBCXX_3.4>
  4010e6:	68 0b 00 00 00       	push   0xb
  4010eb:	e9 30 ff ff ff       	jmp    401020 <.plt>

Disassembly of section .text:

00000000004010f0 <set_fast_math>:
  4010f0:	f3 0f 1e fa          	endbr64 
  4010f4:	0f ae 5c 24 fc       	stmxcsr DWORD PTR [rsp-0x4]
  4010f9:	81 4c 24 fc 40 80 00 00 	or     DWORD PTR [rsp-0x4],0x8040
  401101:	0f ae 54 24 fc       	ldmxcsr DWORD PTR [rsp-0x4]
  401106:	c3                   	ret    
  401107:	66 0f 1f 84 00 00 00 00 00 	nop    WORD PTR [rax+rax*1+0x0]

0000000000401110 <_GLOBAL__sub_I_main.cpp>:
  401110:	50                   	push   rax
  401111:	bf f9 92 56 00       	mov    edi,0x5692f9
  401116:	e8 b5 ff ff ff       	call   4010d0 <std::ios_base::Init::Init()@plt>
  40111b:	bf e0 10 40 00       	mov    edi,0x4010e0
  401120:	be f9 92 56 00       	mov    esi,0x5692f9
  401125:	ba 80 90 56 00       	mov    edx,0x569080
  40112a:	58                   	pop    rax
  40112b:	e9 50 ff ff ff       	jmp    401080 <__cxa_atexit@plt>

0000000000401130 <_start>:
  401130:	f3 0f 1e fa          	endbr64 
  401134:	31 ed                	xor    ebp,ebp
  401136:	49 89 d1             	mov    r9,rdx
  401139:	5e                   	pop    rsi
  40113a:	48 89 e2             	mov    rdx,rsp
  40113d:	48 83 e4 f0          	and    rsp,0xfffffffffffffff0
  401141:	50                   	push   rax
  401142:	54                   	push   rsp
  401143:	49 c7 c0 b0 1d 40 00 	mov    r8,0x401db0
  40114a:	48 c7 c1 40 1d 40 00 	mov    rcx,0x401d40
  401151:	48 c7 c7 60 12 40 00 	mov    rdi,0x401260
  401158:	ff 15 92 7e 16 00    	call   QWORD PTR [rip+0x167e92]        # 568ff0 <__libc_start_main@GLIBC_2.2.5>
  40115e:	f4                   	hlt    
  40115f:	90                   	nop

0000000000401160 <_dl_relocate_static_pie>:
  401160:	f3 0f 1e fa          	endbr64 
  401164:	c3                   	ret    
  401165:	66 2e 0f 1f 84 00 00 00 00 00 	nop    WORD PTR cs:[rax+rax*1+0x0]
  40116f:	90                   	nop

0000000000401170 <deregister_tm_clones>:
  401170:	b8 88 90 56 00       	mov    eax,0x569088
  401175:	48 3d 88 90 56 00    	cmp    rax,0x569088
  40117b:	74 13                	je     401190 <deregister_tm_clones+0x20>
  40117d:	b8 00 00 00 00       	mov    eax,0x0
  401182:	48 85 c0             	test   rax,rax
  401185:	74 09                	je     401190 <deregister_tm_clones+0x20>
  401187:	bf 88 90 56 00       	mov    edi,0x569088
  40118c:	ff e0                	jmp    rax
  40118e:	66 90                	xchg   ax,ax
  401190:	c3                   	ret    
  401191:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 nop WORD PTR cs:[rax+rax*1+0x0]
  40119c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]

00000000004011a0 <register_tm_clones>:
  4011a0:	be 88 90 56 00       	mov    esi,0x569088
  4011a5:	48 81 ee 88 90 56 00 	sub    rsi,0x569088
  4011ac:	48 89 f0             	mov    rax,rsi
  4011af:	48 c1 ee 3f          	shr    rsi,0x3f
  4011b3:	48 c1 f8 03          	sar    rax,0x3
  4011b7:	48 01 c6             	add    rsi,rax
  4011ba:	48 d1 fe             	sar    rsi,1
  4011bd:	74 11                	je     4011d0 <register_tm_clones+0x30>
  4011bf:	b8 00 00 00 00       	mov    eax,0x0
  4011c4:	48 85 c0             	test   rax,rax
  4011c7:	74 07                	je     4011d0 <register_tm_clones+0x30>
  4011c9:	bf 88 90 56 00       	mov    edi,0x569088
  4011ce:	ff e0                	jmp    rax
  4011d0:	c3                   	ret    
  4011d1:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 nop WORD PTR cs:[rax+rax*1+0x0]
  4011dc:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]

00000000004011e0 <__do_global_dtors_aux>:
  4011e0:	f3 0f 1e fa          	endbr64 
  4011e4:	80 3d 0d 81 16 00 00 	cmp    BYTE PTR [rip+0x16810d],0x0        # 5692f8 <completed.0>
  4011eb:	75 13                	jne    401200 <__do_global_dtors_aux+0x20>
  4011ed:	55                   	push   rbp
  4011ee:	48 89 e5             	mov    rbp,rsp
  4011f1:	e8 7a ff ff ff       	call   401170 <deregister_tm_clones>
  4011f6:	c6 05 fb 80 16 00 01 	mov    BYTE PTR [rip+0x1680fb],0x1        # 5692f8 <completed.0>
  4011fd:	5d                   	pop    rbp
  4011fe:	c3                   	ret    
  4011ff:	90                   	nop
  401200:	c3                   	ret    
  401201:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 nop WORD PTR cs:[rax+rax*1+0x0]
  40120c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]

0000000000401210 <frame_dummy>:
  401210:	f3 0f 1e fa          	endbr64 
  401214:	eb 8a                	jmp    4011a0 <register_tm_clones>
  401216:	66 2e 0f 1f 84 00 00 00 00 00 	nop    WORD PTR cs:[rax+rax*1+0x0]

0000000000401220 <Init()>:
  401220:	50                   	push   rax
  401221:	31 ff                	xor    edi,edi
  401223:	e8 18 fe ff ff       	call   401040 <std::ios_base::sync_with_stdio(bool)@plt>
  401228:	48 8b 05 b1 7f 16 00 	mov    rax,QWORD PTR [rip+0x167fb1]        # 5691e0 <std::cin@@GLIBCXX_3.4>
  40122f:	48 8b 40 e8          	mov    rax,QWORD PTR [rax-0x18]
  401233:	48 c7 80 b8 92 56 00 00 00 00 00 	mov    QWORD PTR [rax+0x5692b8],0x0
  40123e:	48 8b 05 7b 7e 16 00 	mov    rax,QWORD PTR [rip+0x167e7b]        # 5690c0 <std::cout@@GLIBCXX_3.4>
  401245:	48 8b 40 e8          	mov    rax,QWORD PTR [rax-0x18]
  401249:	48 c7 80 98 91 56 00 00 00 00 00 	mov    QWORD PTR [rax+0x569198],0x0
  401254:	58                   	pop    rax
  401255:	c3                   	ret    
  401256:	66 2e 0f 1f 84 00 00 00 00 00 	nop    WORD PTR cs:[rax+rax*1+0x0]

0000000000401260 <main>:
  401260:	55                   	push   rbp
  401261:	41 57                	push   r15
  401263:	41 56                	push   r14
  401265:	41 55                	push   r13
  401267:	41 54                	push   r12
  401269:	53                   	push   rbx
  40126a:	48 81 ec 28 02 00 00 	sub    rsp,0x228
  401271:	31 ed                	xor    ebp,ebp
  401273:	31 ff                	xor    edi,edi
  401275:	e8 c6 fd ff ff       	call   401040 <std::ios_base::sync_with_stdio(bool)@plt>
  40127a:	48 8b 05 5f 7f 16 00 	mov    rax,QWORD PTR [rip+0x167f5f]        # 5691e0 <std::cin@@GLIBCXX_3.4>
  401281:	48 8b 40 e8          	mov    rax,QWORD PTR [rax-0x18]
  401285:	48 c7 80 b8 92 56 00 00 00 00 00 	mov    QWORD PTR [rax+0x5692b8],0x0
  401290:	48 8b 05 29 7e 16 00 	mov    rax,QWORD PTR [rip+0x167e29]        # 5690c0 <std::cout@@GLIBCXX_3.4>
  401297:	48 8b 40 e8          	mov    rax,QWORD PTR [rax-0x18]
  40129b:	48 c7 80 98 91 56 00 00 00 00 00 	mov    QWORD PTR [rax+0x569198],0x0
  4012a6:	c6 84 24 a0 01 00 00 00 	mov    BYTE PTR [rsp+0x1a0],0x0
  4012ae:	4c 8d ac 24 a1 01 00 00 	lea    r13,[rsp+0x1a1]
  4012b6:	0f 10 05 73 34 16 00 	movups xmm0,XMMWORD PTR [rip+0x163473]        # 564730 <cohen::chess::io::ascii_board::AsciiBoard::kInitialData>
  4012bd:	0f 11 84 24 a1 01 00 00 	movups XMMWORD PTR [rsp+0x1a1],xmm0
  4012c5:	0f 10 0d 74 34 16 00 	movups xmm1,XMMWORD PTR [rip+0x163474]        # 564740 <cohen::chess::io::ascii_board::AsciiBoard::kInitialData+0x10>
  4012cc:	0f 11 8c 24 b1 01 00 00 	movups XMMWORD PTR [rsp+0x1b1],xmm1
  4012d4:	0f 10 15 75 34 16 00 	movups xmm2,XMMWORD PTR [rip+0x163475]        # 564750 <cohen::chess::io::ascii_board::AsciiBoard::kInitialData+0x20>
  4012db:	0f 11 94 24 c1 01 00 00 	movups XMMWORD PTR [rsp+0x1c1],xmm2
  4012e3:	0f 10 1d 76 34 16 00 	movups xmm3,XMMWORD PTR [rip+0x163476]        # 564760 <cohen::chess::io::ascii_board::AsciiBoard::kInitialData+0x30>
  4012ea:	0f 11 9c 24 d1 01 00 00 	movups XMMWORD PTR [rsp+0x1d1],xmm3
  4012f2:	0f 10 25 77 34 16 00 	movups xmm4,XMMWORD PTR [rip+0x163477]        # 564770 <cohen::chess::io::ascii_board::AsciiBoard::kInitialData+0x40>
  4012f9:	0f 11 a4 24 e1 01 00 00 	movups XMMWORD PTR [rsp+0x1e1],xmm4
  401301:	0f 10 2d 78 34 16 00 	movups xmm5,XMMWORD PTR [rip+0x163478]        # 564780 <cohen::chess::io::ascii_board::AsciiBoard::kInitialData+0x50>
  401308:	0f 11 ac 24 f1 01 00 00 	movups XMMWORD PTR [rsp+0x1f1],xmm5
  401310:	0f 10 35 79 34 16 00 	movups xmm6,XMMWORD PTR [rip+0x163479]        # 564790 <cohen::chess::io::ascii_board::AsciiBoard::kInitialData+0x60>
  401317:	0f 11 b4 24 01 02 00 00 	movups XMMWORD PTR [rsp+0x201],xmm6
  40131f:	0f 10 3d 7a 34 16 00 	movups xmm7,XMMWORD PTR [rip+0x16347a]        # 5647a0 <cohen::chess::io::ascii_board::AsciiBoard::kInitialData+0x70>
  401326:	0f 11 bc 24 11 02 00 00 	movups XMMWORD PTR [rsp+0x211],xmm7
  40132e:	c6 84 24 18 01 00 00 00 	mov    BYTE PTR [rsp+0x118],0x0
  401336:	4c 8d a4 24 19 01 00 00 	lea    r12,[rsp+0x119]
  40133e:	0f 11 84 24 19 01 00 00 	movups XMMWORD PTR [rsp+0x119],xmm0
  401346:	0f 11 8c 24 29 01 00 00 	movups XMMWORD PTR [rsp+0x129],xmm1
  40134e:	0f 11 94 24 39 01 00 00 	movups XMMWORD PTR [rsp+0x139],xmm2
  401356:	0f 11 9c 24 49 01 00 00 	movups XMMWORD PTR [rsp+0x149],xmm3
  40135e:	0f 11 a4 24 59 01 00 00 	movups XMMWORD PTR [rsp+0x159],xmm4
  401366:	0f 11 ac 24 69 01 00 00 	movups XMMWORD PTR [rsp+0x169],xmm5
  40136e:	0f 11 b4 24 79 01 00 00 	movups XMMWORD PTR [rsp+0x179],xmm6
  401376:	0f 11 bc 24 89 01 00 00 	movups XMMWORD PTR [rsp+0x189],xmm7
  40137e:	c6 84 24 90 00 00 00 00 	mov    BYTE PTR [rsp+0x90],0x0
  401386:	4c 8d bc 24 91 00 00 00 	lea    r15,[rsp+0x91]
  40138e:	0f 11 84 24 91 00 00 00 	movups XMMWORD PTR [rsp+0x91],xmm0
  401396:	0f 11 8c 24 a1 00 00 00 	movups XMMWORD PTR [rsp+0xa1],xmm1
  40139e:	0f 11 94 24 b1 00 00 00 	movups XMMWORD PTR [rsp+0xb1],xmm2
  4013a6:	0f 11 9c 24 c1 00 00 00 	movups XMMWORD PTR [rsp+0xc1],xmm3
  4013ae:	0f 11 a4 24 d1 00 00 00 	movups XMMWORD PTR [rsp+0xd1],xmm4
  4013b6:	0f 11 ac 24 e1 00 00 00 	movups XMMWORD PTR [rsp+0xe1],xmm5
  4013be:	0f 11 b4 24 f1 00 00 00 	movups XMMWORD PTR [rsp+0xf1],xmm6
  4013c6:	0f 11 bc 24 01 01 00 00 	movups XMMWORD PTR [rsp+0x101],xmm7
  4013ce:	c6 44 24 08 00       	mov    BYTE PTR [rsp+0x8],0x0
  4013d3:	4c 8d 74 24 09       	lea    r14,[rsp+0x9]
  4013d8:	0f 11 44 24 09       	movups XMMWORD PTR [rsp+0x9],xmm0
  4013dd:	0f 11 4c 24 19       	movups XMMWORD PTR [rsp+0x19],xmm1
  4013e2:	0f 11 54 24 29       	movups XMMWORD PTR [rsp+0x29],xmm2
  4013e7:	0f 11 5c 24 39       	movups XMMWORD PTR [rsp+0x39],xmm3
  4013ec:	0f 11 64 24 49       	movups XMMWORD PTR [rsp+0x49],xmm4
  4013f1:	0f 11 6c 24 59       	movups XMMWORD PTR [rsp+0x59],xmm5
  4013f6:	0f 11 74 24 69       	movups XMMWORD PTR [rsp+0x69],xmm6
  4013fb:	0f 11 7c 24 79       	movups XMMWORD PTR [rsp+0x79],xmm7
  401400:	40 b6 31             	mov    sil,0x31
  401403:	b1 01                	mov    cl,0x1
  401405:	31 c0                	xor    eax,eax
  401407:	31 d2                	xor    edx,edx
  401409:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  401410:	80 fa 02             	cmp    dl,0x2
  401413:	0f 83 01 09 00 00    	jae    401d1a <main+0xaba>
  401419:	89 c3                	mov    ebx,eax
  40141b:	80 e3 07             	and    bl,0x7
  40141e:	0f b6 c9             	movzx  ecx,cl
  401421:	8d 3c cd 00 00 00 00 	lea    edi,[rcx*8+0x0]
  401428:	29 cf                	sub    edi,ecx
  40142a:	40 30 ef             	xor    dil,bpl
  40142d:	0f b6 ca             	movzx  ecx,dl
  401430:	8d 14 cd 00 00 00 00 	lea    edx,[rcx*8+0x0]
  401437:	29 ca                	sub    edx,ecx
  401439:	30 da                	xor    dl,bl
  40143b:	40 0f be cf          	movsx  ecx,dil
  40143f:	c1 e1 04             	shl    ecx,0x4
  401442:	0f be d2             	movsx  edx,dl
  401445:	8d 0c 51             	lea    ecx,[rcx+rdx*2]
  401448:	48 63 c9             	movsxd rcx,ecx
  40144b:	40 88 b4 0c a1 01 00 00 	mov    BYTE PTR [rsp+rcx*1+0x1a1],sil
  401453:	3c 3f                	cmp    al,0x3f
  401455:	74 27                	je     40147e <main+0x21e>
  401457:	04 01                	add    al,0x1
  401459:	0f b6 94 24 a0 01 00 00 	movzx  edx,BYTE PTR [rsp+0x1a0]
  401461:	0f b6 e8             	movzx  ebp,al
  401464:	48 c1 ed 03          	shr    rbp,0x3
  401468:	0f b6 b5 88 20 40 00 	movzx  esi,BYTE PTR [rbp+0x402088]
  40146f:	89 d1                	mov    ecx,edx
  401471:	80 f1 01             	xor    cl,0x1
  401474:	80 f9 02             	cmp    cl,0x2
  401477:	72 97                	jb     401410 <main+0x1b0>
  401479:	e9 89 01 00 00       	jmp    401607 <main+0x3a7>
  40147e:	b1 41                	mov    cl,0x41
  401480:	b3 01                	mov    bl,0x1
  401482:	31 d2                	xor    edx,edx
  401484:	31 c0                	xor    eax,eax
  401486:	31 f6                	xor    esi,esi
  401488:	0f 1f 84 00 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]
  401490:	40 80 fe 02          	cmp    sil,0x2
  401494:	0f 83 80 08 00 00    	jae    401d1a <main+0xaba>
  40149a:	0f b6 fb             	movzx  edi,bl
  40149d:	8d 2c fd 00 00 00 00 	lea    ebp,[rdi*8+0x0]
  4014a4:	29 fd                	sub    ebp,edi
  4014a6:	89 c3                	mov    ebx,eax
  4014a8:	c0 eb 03             	shr    bl,0x3
  4014ab:	40 30 eb             	xor    bl,bpl
  4014ae:	40 0f b6 f6          	movzx  esi,sil
  4014b2:	8d 3c f5 00 00 00 00 	lea    edi,[rsi*8+0x0]
  4014b9:	29 f7                	sub    edi,esi
  4014bb:	40 30 d7             	xor    dil,dl
  4014be:	0f be d3             	movsx  edx,bl
  4014c1:	c1 e2 04             	shl    edx,0x4
  4014c4:	40 0f be f7          	movsx  esi,dil
  4014c8:	8d 14 72             	lea    edx,[rdx+rsi*2]
  4014cb:	48 63 d2             	movsxd rdx,edx
  4014ce:	88 8c 14 19 01 00 00 	mov    BYTE PTR [rsp+rdx*1+0x119],cl
  4014d5:	3c 3f                	cmp    al,0x3f
  4014d7:	74 26                	je     4014ff <main+0x29f>
  4014d9:	04 01                	add    al,0x1
  4014db:	0f b6 b4 24 18 01 00 00 	movzx  esi,BYTE PTR [rsp+0x118]
  4014e3:	0f b6 d0             	movzx  edx,al
  4014e6:	83 e2 07             	and    edx,0x7
  4014e9:	0f b6 8a 91 20 40 00 	movzx  ecx,BYTE PTR [rdx+0x402091]
  4014f0:	89 f3                	mov    ebx,esi
  4014f2:	80 f3 01             	xor    bl,0x1
  4014f5:	80 fb 02             	cmp    bl,0x2
  4014f8:	72 96                	jb     401490 <main+0x230>
  4014fa:	e9 08 01 00 00       	jmp    401607 <main+0x3a7>
  4014ff:	b1 38                	mov    cl,0x38
  401501:	b0 01                	mov    al,0x1
  401503:	31 d2                	xor    edx,edx
  401505:	b3 01                	mov    bl,0x1
  401507:	31 ff                	xor    edi,edi
  401509:	31 f6                	xor    esi,esi
  40150b:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
  401510:	40 80 fe 02          	cmp    sil,0x2
  401514:	0f 83 00 08 00 00    	jae    401d1a <main+0xaba>
  40151a:	0f b6 eb             	movzx  ebp,bl
  40151d:	8d 1c ed 00 00 00 00 	lea    ebx,[rbp*8+0x0]
  401524:	29 eb                	sub    ebx,ebp
  401526:	40 30 fb             	xor    bl,dil
  401529:	40 0f b6 f6          	movzx  esi,sil
  40152d:	8d 3c f5 00 00 00 00 	lea    edi,[rsi*8+0x0]
  401534:	29 f7                	sub    edi,esi
  401536:	40 30 d7             	xor    dil,dl
  401539:	0f be d3             	movsx  edx,bl
  40153c:	c1 e2 04             	shl    edx,0x4
  40153f:	40 0f be f7          	movsx  esi,dil
  401543:	8d 14 72             	lea    edx,[rdx+rsi*2]
  401546:	48 63 d2             	movsxd rdx,edx
  401549:	88 8c 14 91 00 00 00 	mov    BYTE PTR [rsp+rdx*1+0x91],cl
  401550:	3c 40                	cmp    al,0x40
  401552:	74 34                	je     401588 <main+0x328>
  401554:	0f b6 b4 24 90 00 00 00 	movzx  esi,BYTE PTR [rsp+0x90]
  40155c:	0f b6 f8             	movzx  edi,al
  40155f:	48 c1 ef 03          	shr    rdi,0x3
  401563:	89 c2                	mov    edx,eax
  401565:	80 e2 07             	and    dl,0x7
  401568:	0f b6 ca             	movzx  ecx,dl
  40156b:	48 83 f1 07          	xor    rcx,0x7
  40156f:	0f b6 8c 39 9a 20 40 00 	movzx  ecx,BYTE PTR [rcx+rdi*1+0x40209a]
  401577:	89 f3                	mov    ebx,esi
  401579:	80 f3 01             	xor    bl,0x1
  40157c:	04 01                	add    al,0x1
  40157e:	80 fb 02             	cmp    bl,0x2
  401581:	72 8d                	jb     401510 <main+0x2b0>
  401583:	e9 7f 00 00 00       	jmp    401607 <main+0x3a7>
  401588:	b1 31                	mov    cl,0x31
  40158a:	b0 01                	mov    al,0x1
  40158c:	31 d2                	xor    edx,edx
  40158e:	b3 01                	mov    bl,0x1
  401590:	31 ff                	xor    edi,edi
  401592:	31 f6                	xor    esi,esi
  401594:	66 2e 0f 1f 84 00 00 00 00 00 	nop    WORD PTR cs:[rax+rax*1+0x0]
  40159e:	66 90                	xchg   ax,ax
  4015a0:	40 80 fe 02          	cmp    sil,0x2
  4015a4:	0f 83 70 07 00 00    	jae    401d1a <main+0xaba>
  4015aa:	0f b6 eb             	movzx  ebp,bl
  4015ad:	8d 1c ed 00 00 00 00 	lea    ebx,[rbp*8+0x0]
  4015b4:	29 eb                	sub    ebx,ebp
  4015b6:	40 30 fb             	xor    bl,dil
  4015b9:	40 0f b6 f6          	movzx  esi,sil
  4015bd:	8d 3c f5 00 00 00 00 	lea    edi,[rsi*8+0x0]
  4015c4:	29 f7                	sub    edi,esi
  4015c6:	40 30 d7             	xor    dil,dl
  4015c9:	0f be d3             	movsx  edx,bl
  4015cc:	c1 e2 04             	shl    edx,0x4
  4015cf:	40 0f be f7          	movsx  esi,dil
  4015d3:	8d 14 72             	lea    edx,[rdx+rsi*2]
  4015d6:	48 63 d2             	movsxd rdx,edx
  4015d9:	88 4c 14 09          	mov    BYTE PTR [rsp+rdx*1+0x9],cl
  4015dd:	3c 40                	cmp    al,0x40
  4015df:	74 3f                	je     401620 <main+0x3c0>
  4015e1:	0f b6 74 24 08       	movzx  esi,BYTE PTR [rsp+0x8]
  4015e6:	0f b6 d0             	movzx  edx,al
  4015e9:	48 89 d7             	mov    rdi,rdx
  4015ec:	48 c1 ef 03          	shr    rdi,0x3
  4015f0:	83 e2 07             	and    edx,0x7
  4015f3:	0f b6 8c 17 9a 20 40 00 	movzx  ecx,BYTE PTR [rdi+rdx*1+0x40209a]
  4015fb:	89 f3                	mov    ebx,esi
  4015fd:	80 f3 01             	xor    bl,0x1
  401600:	04 01                	add    al,0x1
  401602:	80 fb 02             	cmp    bl,0x2
  401605:	72 99                	jb     4015a0 <main+0x340>
  401607:	bf b2 22 40 00       	mov    edi,0x4022b2
  40160c:	be 08 22 40 00       	mov    esi,0x402208
  401611:	b9 2a 22 40 00       	mov    ecx,0x40222a
  401616:	ba 23 00 00 00       	mov    edx,0x23
  40161b:	e8 30 fa ff ff       	call   401050 <__assert_fail@plt>
  401620:	bf c0 90 56 00       	mov    edi,0x5690c0
  401625:	be aa 20 40 00       	mov    esi,0x4020aa
  40162a:	ba 0b 00 00 00       	mov    edx,0xb
  40162f:	e8 5c fa ff ff       	call   401090 <std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)@plt>
  401634:	48 8b 05 85 7a 16 00 	mov    rax,QWORD PTR [rip+0x167a85]        # 5690c0 <std::cout@@GLIBCXX_3.4>
  40163b:	48 8b 40 e8          	mov    rax,QWORD PTR [rax-0x18]
  40163f:	48 8b 98 b0 91 56 00 	mov    rbx,QWORD PTR [rax+0x5691b0]
  401646:	48 85 db             	test   rbx,rbx
  401649:	0f 84 e4 06 00 00    	je     401d33 <main+0xad3>
  40164f:	80 7b 38 00          	cmp    BYTE PTR [rbx+0x38],0x0
  401653:	74 05                	je     40165a <main+0x3fa>
  401655:	8a 43 43             	mov    al,BYTE PTR [rbx+0x43]
  401658:	eb 16                	jmp    401670 <main+0x410>
  40165a:	48 89 df             	mov    rdi,rbx
  40165d:	e8 3e fa ff ff       	call   4010a0 <std::ctype<char>::_M_widen_init() const@plt>
  401662:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  401665:	48 89 df             	mov    rdi,rbx
  401668:	be 0a 00 00 00       	mov    esi,0xa
  40166d:	ff 50 30             	call   QWORD PTR [rax+0x30]
  401670:	0f be f0             	movsx  esi,al
  401673:	bf c0 90 56 00       	mov    edi,0x5690c0
  401678:	e8 b3 f9 ff ff       	call   401030 <std::ostream::put(char)@plt>
  40167d:	48 89 c7             	mov    rdi,rax
  401680:	e8 eb f9 ff ff       	call   401070 <std::ostream::flush()@plt>
  401685:	ba 80 00 00 00       	mov    edx,0x80
  40168a:	48 89 c7             	mov    rdi,rax
  40168d:	4c 89 ee             	mov    rsi,r13
  401690:	e8 2b fa ff ff       	call   4010c0 <std::ostream::write(char const*, long)@plt>
  401695:	49 89 c5             	mov    r13,rax
  401698:	48 8b 00             	mov    rax,QWORD PTR [rax]
  40169b:	48 8b 40 e8          	mov    rax,QWORD PTR [rax-0x18]
  40169f:	49 8b 9c 05 f0 00 00 00 	mov    rbx,QWORD PTR [r13+rax*1+0xf0]
  4016a7:	48 85 db             	test   rbx,rbx
  4016aa:	0f 84 83 06 00 00    	je     401d33 <main+0xad3>
  4016b0:	80 7b 38 00          	cmp    BYTE PTR [rbx+0x38],0x0
  4016b4:	74 05                	je     4016bb <main+0x45b>
  4016b6:	8a 43 43             	mov    al,BYTE PTR [rbx+0x43]
  4016b9:	eb 16                	jmp    4016d1 <main+0x471>
  4016bb:	48 89 df             	mov    rdi,rbx
  4016be:	e8 dd f9 ff ff       	call   4010a0 <std::ctype<char>::_M_widen_init() const@plt>
  4016c3:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  4016c6:	48 89 df             	mov    rdi,rbx
  4016c9:	be 0a 00 00 00       	mov    esi,0xa
  4016ce:	ff 50 30             	call   QWORD PTR [rax+0x30]
  4016d1:	0f be f0             	movsx  esi,al
  4016d4:	4c 89 ef             	mov    rdi,r13
  4016d7:	e8 54 f9 ff ff       	call   401030 <std::ostream::put(char)@plt>
  4016dc:	48 89 c7             	mov    rdi,rax
  4016df:	e8 8c f9 ff ff       	call   401070 <std::ostream::flush()@plt>
  4016e4:	bf c0 90 56 00       	mov    edi,0x5690c0
  4016e9:	be b6 20 40 00       	mov    esi,0x4020b6
  4016ee:	ba 0b 00 00 00       	mov    edx,0xb
  4016f3:	e8 98 f9 ff ff       	call   401090 <std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)@plt>
  4016f8:	48 8b 05 c1 79 16 00 	mov    rax,QWORD PTR [rip+0x1679c1]        # 5690c0 <std::cout@@GLIBCXX_3.4>
  4016ff:	48 8b 40 e8          	mov    rax,QWORD PTR [rax-0x18]
  401703:	48 8b 98 b0 91 56 00 	mov    rbx,QWORD PTR [rax+0x5691b0]
  40170a:	48 85 db             	test   rbx,rbx
  40170d:	0f 84 20 06 00 00    	je     401d33 <main+0xad3>
  401713:	80 7b 38 00          	cmp    BYTE PTR [rbx+0x38],0x0
  401717:	74 05                	je     40171e <main+0x4be>
  401719:	8a 43 43             	mov    al,BYTE PTR [rbx+0x43]
  40171c:	eb 16                	jmp    401734 <main+0x4d4>
  40171e:	48 89 df             	mov    rdi,rbx
  401721:	e8 7a f9 ff ff       	call   4010a0 <std::ctype<char>::_M_widen_init() const@plt>
  401726:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  401729:	48 89 df             	mov    rdi,rbx
  40172c:	be 0a 00 00 00       	mov    esi,0xa
  401731:	ff 50 30             	call   QWORD PTR [rax+0x30]
  401734:	0f be f0             	movsx  esi,al
  401737:	bf c0 90 56 00       	mov    edi,0x5690c0
  40173c:	e8 ef f8 ff ff       	call   401030 <std::ostream::put(char)@plt>
  401741:	48 89 c7             	mov    rdi,rax
  401744:	e8 27 f9 ff ff       	call   401070 <std::ostream::flush()@plt>
  401749:	ba 80 00 00 00       	mov    edx,0x80
  40174e:	48 89 c7             	mov    rdi,rax
  401751:	4c 89 e6             	mov    rsi,r12
  401754:	e8 67 f9 ff ff       	call   4010c0 <std::ostream::write(char const*, long)@plt>
  401759:	49 89 c4             	mov    r12,rax
  40175c:	48 8b 00             	mov    rax,QWORD PTR [rax]
  40175f:	48 8b 40 e8          	mov    rax,QWORD PTR [rax-0x18]
  401763:	49 8b 9c 04 f0 00 00 00 	mov    rbx,QWORD PTR [r12+rax*1+0xf0]
  40176b:	48 85 db             	test   rbx,rbx
  40176e:	0f 84 bf 05 00 00    	je     401d33 <main+0xad3>
  401774:	80 7b 38 00          	cmp    BYTE PTR [rbx+0x38],0x0
  401778:	74 05                	je     40177f <main+0x51f>
  40177a:	8a 43 43             	mov    al,BYTE PTR [rbx+0x43]
  40177d:	eb 16                	jmp    401795 <main+0x535>
  40177f:	48 89 df             	mov    rdi,rbx
  401782:	e8 19 f9 ff ff       	call   4010a0 <std::ctype<char>::_M_widen_init() const@plt>
  401787:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  40178a:	48 89 df             	mov    rdi,rbx
  40178d:	be 0a 00 00 00       	mov    esi,0xa
  401792:	ff 50 30             	call   QWORD PTR [rax+0x30]
  401795:	0f be f0             	movsx  esi,al
  401798:	4c 89 e7             	mov    rdi,r12
  40179b:	e8 90 f8 ff ff       	call   401030 <std::ostream::put(char)@plt>
  4017a0:	48 89 c7             	mov    rdi,rax
  4017a3:	e8 c8 f8 ff ff       	call   401070 <std::ostream::flush()@plt>
  4017a8:	bf c0 90 56 00       	mov    edi,0x5690c0
  4017ad:	be c2 20 40 00       	mov    esi,0x4020c2
  4017b2:	ba 0b 00 00 00       	mov    edx,0xb
  4017b7:	e8 d4 f8 ff ff       	call   401090 <std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)@plt>
  4017bc:	48 8b 05 fd 78 16 00 	mov    rax,QWORD PTR [rip+0x1678fd]        # 5690c0 <std::cout@@GLIBCXX_3.4>
  4017c3:	48 8b 40 e8          	mov    rax,QWORD PTR [rax-0x18]
  4017c7:	48 8b 98 b0 91 56 00 	mov    rbx,QWORD PTR [rax+0x5691b0]
  4017ce:	48 85 db             	test   rbx,rbx
  4017d1:	0f 84 5c 05 00 00    	je     401d33 <main+0xad3>
  4017d7:	80 7b 38 00          	cmp    BYTE PTR [rbx+0x38],0x0
  4017db:	74 05                	je     4017e2 <main+0x582>
  4017dd:	8a 43 43             	mov    al,BYTE PTR [rbx+0x43]
  4017e0:	eb 16                	jmp    4017f8 <main+0x598>
  4017e2:	48 89 df             	mov    rdi,rbx
  4017e5:	e8 b6 f8 ff ff       	call   4010a0 <std::ctype<char>::_M_widen_init() const@plt>
  4017ea:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  4017ed:	48 89 df             	mov    rdi,rbx
  4017f0:	be 0a 00 00 00       	mov    esi,0xa
  4017f5:	ff 50 30             	call   QWORD PTR [rax+0x30]
  4017f8:	0f be f0             	movsx  esi,al
  4017fb:	bf c0 90 56 00       	mov    edi,0x5690c0
  401800:	e8 2b f8 ff ff       	call   401030 <std::ostream::put(char)@plt>
  401805:	48 89 c7             	mov    rdi,rax
  401808:	e8 63 f8 ff ff       	call   401070 <std::ostream::flush()@plt>
  40180d:	ba 80 00 00 00       	mov    edx,0x80
  401812:	48 89 c7             	mov    rdi,rax
  401815:	4c 89 fe             	mov    rsi,r15
  401818:	e8 a3 f8 ff ff       	call   4010c0 <std::ostream::write(char const*, long)@plt>
  40181d:	49 89 c7             	mov    r15,rax
  401820:	48 8b 00             	mov    rax,QWORD PTR [rax]
  401823:	48 8b 40 e8          	mov    rax,QWORD PTR [rax-0x18]
  401827:	49 8b 9c 07 f0 00 00 00 	mov    rbx,QWORD PTR [r15+rax*1+0xf0]
  40182f:	48 85 db             	test   rbx,rbx
  401832:	0f 84 fb 04 00 00    	je     401d33 <main+0xad3>
  401838:	80 7b 38 00          	cmp    BYTE PTR [rbx+0x38],0x0
  40183c:	74 05                	je     401843 <main+0x5e3>
  40183e:	8a 43 43             	mov    al,BYTE PTR [rbx+0x43]
  401841:	eb 16                	jmp    401859 <main+0x5f9>
  401843:	48 89 df             	mov    rdi,rbx
  401846:	e8 55 f8 ff ff       	call   4010a0 <std::ctype<char>::_M_widen_init() const@plt>
  40184b:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  40184e:	48 89 df             	mov    rdi,rbx
  401851:	be 0a 00 00 00       	mov    esi,0xa
  401856:	ff 50 30             	call   QWORD PTR [rax+0x30]
  401859:	0f be f0             	movsx  esi,al
  40185c:	4c 89 ff             	mov    rdi,r15
  40185f:	e8 cc f7 ff ff       	call   401030 <std::ostream::put(char)@plt>
  401864:	48 89 c7             	mov    rdi,rax
  401867:	e8 04 f8 ff ff       	call   401070 <std::ostream::flush()@plt>
  40186c:	bf c0 90 56 00       	mov    edi,0x5690c0
  401871:	be ce 20 40 00       	mov    esi,0x4020ce
  401876:	ba 0b 00 00 00       	mov    edx,0xb
  40187b:	e8 10 f8 ff ff       	call   401090 <std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)@plt>
  401880:	48 8b 05 39 78 16 00 	mov    rax,QWORD PTR [rip+0x167839]        # 5690c0 <std::cout@@GLIBCXX_3.4>
  401887:	48 8b 40 e8          	mov    rax,QWORD PTR [rax-0x18]
  40188b:	48 8b 98 b0 91 56 00 	mov    rbx,QWORD PTR [rax+0x5691b0]
  401892:	48 85 db             	test   rbx,rbx
  401895:	0f 84 98 04 00 00    	je     401d33 <main+0xad3>
  40189b:	80 7b 38 00          	cmp    BYTE PTR [rbx+0x38],0x0
  40189f:	74 05                	je     4018a6 <main+0x646>
  4018a1:	8a 43 43             	mov    al,BYTE PTR [rbx+0x43]
  4018a4:	eb 16                	jmp    4018bc <main+0x65c>
  4018a6:	48 89 df             	mov    rdi,rbx
  4018a9:	e8 f2 f7 ff ff       	call   4010a0 <std::ctype<char>::_M_widen_init() const@plt>
  4018ae:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  4018b1:	48 89 df             	mov    rdi,rbx
  4018b4:	be 0a 00 00 00       	mov    esi,0xa
  4018b9:	ff 50 30             	call   QWORD PTR [rax+0x30]
  4018bc:	0f be f0             	movsx  esi,al
  4018bf:	bf c0 90 56 00       	mov    edi,0x5690c0
  4018c4:	e8 67 f7 ff ff       	call   401030 <std::ostream::put(char)@plt>
  4018c9:	48 89 c7             	mov    rdi,rax
  4018cc:	e8 9f f7 ff ff       	call   401070 <std::ostream::flush()@plt>
  4018d1:	ba 80 00 00 00       	mov    edx,0x80
  4018d6:	48 89 c7             	mov    rdi,rax
  4018d9:	4c 89 f6             	mov    rsi,r14
  4018dc:	e8 df f7 ff ff       	call   4010c0 <std::ostream::write(char const*, long)@plt>
  4018e1:	49 89 c6             	mov    r14,rax
  4018e4:	48 8b 00             	mov    rax,QWORD PTR [rax]
  4018e7:	48 8b 40 e8          	mov    rax,QWORD PTR [rax-0x18]
  4018eb:	49 8b 9c 06 f0 00 00 00 	mov    rbx,QWORD PTR [r14+rax*1+0xf0]
  4018f3:	48 85 db             	test   rbx,rbx
  4018f6:	0f 84 37 04 00 00    	je     401d33 <main+0xad3>
  4018fc:	80 7b 38 00          	cmp    BYTE PTR [rbx+0x38],0x0
  401900:	74 05                	je     401907 <main+0x6a7>
  401902:	8a 43 43             	mov    al,BYTE PTR [rbx+0x43]
  401905:	eb 16                	jmp    40191d <main+0x6bd>
  401907:	48 89 df             	mov    rdi,rbx
  40190a:	e8 91 f7 ff ff       	call   4010a0 <std::ctype<char>::_M_widen_init() const@plt>
  40190f:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  401912:	48 89 df             	mov    rdi,rbx
  401915:	be 0a 00 00 00       	mov    esi,0xa
  40191a:	ff 50 30             	call   QWORD PTR [rax+0x30]
  40191d:	0f be f0             	movsx  esi,al
  401920:	4c 89 f7             	mov    rdi,r14
  401923:	e8 08 f7 ff ff       	call   401030 <std::ostream::put(char)@plt>
  401928:	48 89 c7             	mov    rdi,rax
  40192b:	e8 40 f7 ff ff       	call   401070 <std::ostream::flush()@plt>
  401930:	31 c0                	xor    eax,eax
  401932:	66 2e 0f 1f 84 00 00 00 00 00 	nop    WORD PTR cs:[rax+rax*1+0x0]
  40193c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
  401940:	48 89 04 24          	mov    QWORD PTR [rsp],rax
  401944:	0f b6 d0             	movzx  edx,al
  401947:	48 8d 34 d5 00 00 00 00 	lea    rsi,[rdx*8+0x0]
  40194f:	4c 8b 34 d5 b0 47 56 00 	mov    r14,QWORD PTR [rdx*8+0x5647b0]
  401957:	4c 8b 24 d5 b0 49 56 00 	mov    r12,QWORD PTR [rdx*8+0x5649b0]
  40195f:	4c 8b 2c d5 b0 4b 56 00 	mov    r13,QWORD PTR [rdx*8+0x564bb0]
  401967:	4c 8b 3c d5 b0 4d 56 00 	mov    r15,QWORD PTR [rdx*8+0x564db0]
  40196f:	48 8b 1c d5 b0 4f 56 00 	mov    rbx,QWORD PTR [rdx*8+0x564fb0]
  401977:	48 c1 e2 05          	shl    rdx,0x5
  40197b:	4c 8b 8a c0 51 56 00 	mov    r9,QWORD PTR [rdx+0x5651c0]
  401982:	4c 8b 92 b8 51 56 00 	mov    r10,QWORD PTR [rdx+0x5651b8]
  401989:	8b 8a c8 51 56 00    	mov    ecx,DWORD PTR [rdx+0x5651c8]
  40198f:	4c 8b 9a b0 51 56 00 	mov    r11,QWORD PTR [rdx+0x5651b0]
  401996:	48 8d 14 76          	lea    rdx,[rsi+rsi*2]
  40199a:	48 81 c2 c0 59 56 00 	add    rdx,0x5659c0
  4019a1:	31 f6                	xor    esi,esi
  4019a3:	66 2e 0f 1f 84 00 00 00 00 00 	nop    WORD PTR cs:[rax+rax*1+0x0]
  4019ad:	0f 1f 00             	nop    DWORD PTR [rax]
  4019b0:	4c 89 e7             	mov    rdi,r12
  4019b3:	48 21 f7             	and    rdi,rsi
  4019b6:	48 b8 00 00 00 00 00 00 00 80 	movabs rax,0x8000000000000000
  4019c0:	48 09 c7             	or     rdi,rax
  4019c3:	48 0f bc ff          	bsf    rdi,rdi
  4019c7:	48 8b 3c fd b0 49 56 00 	mov    rdi,QWORD PTR [rdi*8+0x5649b0]
  4019cf:	4c 31 e7             	xor    rdi,r12
  4019d2:	4c 89 ed             	mov    rbp,r13
  4019d5:	48 21 f5             	and    rbp,rsi
  4019d8:	48 09 c5             	or     rbp,rax
  4019db:	48 0f bc ed          	bsf    rbp,rbp
  4019df:	48 8b 2c ed b0 4b 56 00 	mov    rbp,QWORD PTR [rbp*8+0x564bb0]
  4019e7:	4c 31 ed             	xor    rbp,r13
  4019ea:	48 09 fd             	or     rbp,rdi
  4019ed:	4c 89 ff             	mov    rdi,r15
  4019f0:	48 21 f7             	and    rdi,rsi
  4019f3:	48 83 cf 01          	or     rdi,0x1
  4019f7:	48 0f bd ff          	bsr    rdi,rdi
  4019fb:	4c 8b 04 fd b0 4d 56 00 	mov    r8,QWORD PTR [rdi*8+0x564db0]
  401a03:	4d 31 f8             	xor    r8,r15
  401a06:	48 89 df             	mov    rdi,rbx
  401a09:	48 21 f7             	and    rdi,rsi
  401a0c:	48 83 cf 01          	or     rdi,0x1
  401a10:	48 0f bd ff          	bsr    rdi,rdi
  401a14:	48 8b 3c fd b0 4f 56 00 	mov    rdi,QWORD PTR [rdi*8+0x564fb0]
  401a1c:	48 31 df             	xor    rdi,rbx
  401a1f:	4c 09 c7             	or     rdi,r8
  401a22:	4c 89 c8             	mov    rax,r9
  401a25:	48 21 f0             	and    rax,rsi
  401a28:	49 0f af c2          	imul   rax,r10
  401a2c:	48 d3 e8             	shr    rax,cl
  401a2f:	48 09 ef             	or     rdi,rbp
  401a32:	4c 01 d8             	add    rax,r11
  401a35:	48 3b 3c c5 80 23 40 00 	cmp    rdi,QWORD PTR [rax*8+0x402380]
  401a3d:	0f 85 73 02 00 00    	jne    401cb6 <main+0xa56>
  401a43:	48 8b 02             	mov    rax,QWORD PTR [rdx]
  401a46:	48 09 f0             	or     rax,rsi
  401a49:	48 0f af 42 f8       	imul   rax,QWORD PTR [rdx-0x8]
  401a4e:	48 c1 e8 37          	shr    rax,0x37
  401a52:	48 03 42 f0          	add    rax,QWORD PTR [rdx-0x10]
  401a56:	48 3b 3c c5 58 79 4b 00 	cmp    rdi,QWORD PTR [rax*8+0x4b7958]
  401a5e:	0f 85 6b 02 00 00    	jne    401ccf <main+0xa6f>
  401a64:	4c 29 f6             	sub    rsi,r14
  401a67:	4c 21 f6             	and    rsi,r14
  401a6a:	0f 85 40 ff ff ff    	jne    4019b0 <main+0x750>
  401a70:	48 8b 04 24          	mov    rax,QWORD PTR [rsp]
  401a74:	04 01                	add    al,0x1
  401a76:	3c 40                	cmp    al,0x40
  401a78:	0f 85 c2 fe ff ff    	jne    401940 <main+0x6e0>
  401a7e:	45 31 c0             	xor    r8d,r8d
  401a81:	66 2e 0f 1f 84 00 00 00 00 00 	nop    WORD PTR cs:[rax+rax*1+0x0]
  401a8b:	0f 1f 44 00 00       	nop    DWORD PTR [rax+rax*1+0x0]
  401a90:	41 0f b6 d0          	movzx  edx,r8b
  401a94:	48 8d 34 d5 00 00 00 00 	lea    rsi,[rdx*8+0x0]
  401a9c:	4c 8b 34 d5 b0 5f 56 00 	mov    r14,QWORD PTR [rdx*8+0x565fb0]
  401aa4:	4c 8b 24 d5 b0 61 56 00 	mov    r12,QWORD PTR [rdx*8+0x5661b0]
  401aac:	4c 8b 2c d5 b0 63 56 00 	mov    r13,QWORD PTR [rdx*8+0x5663b0]
  401ab4:	4c 8b 3c d5 b0 65 56 00 	mov    r15,QWORD PTR [rdx*8+0x5665b0]
  401abc:	48 8b 1c d5 b0 67 56 00 	mov    rbx,QWORD PTR [rdx*8+0x5667b0]
  401ac4:	48 c1 e2 05          	shl    rdx,0x5
  401ac8:	4c 8b 8a c0 69 56 00 	mov    r9,QWORD PTR [rdx+0x5669c0]
  401acf:	4c 8b 92 b8 69 56 00 	mov    r10,QWORD PTR [rdx+0x5669b8]
  401ad6:	8b 8a c8 69 56 00    	mov    ecx,DWORD PTR [rdx+0x5669c8]
  401adc:	4c 8b 9a b0 69 56 00 	mov    r11,QWORD PTR [rdx+0x5669b0]
  401ae3:	48 8d 14 76          	lea    rdx,[rsi+rsi*2]
  401ae7:	48 81 c2 c0 71 56 00 	add    rdx,0x5671c0
  401aee:	31 f6                	xor    esi,esi
  401af0:	4c 89 e7             	mov    rdi,r12
  401af3:	48 21 f7             	and    rdi,rsi
  401af6:	48 b8 00 00 00 00 00 00 00 80 	movabs rax,0x8000000000000000
  401b00:	48 09 c7             	or     rdi,rax
  401b03:	48 0f bc ff          	bsf    rdi,rdi
  401b07:	48 8b 3c fd b0 61 56 00 	mov    rdi,QWORD PTR [rdi*8+0x5661b0]
  401b0f:	4c 31 e7             	xor    rdi,r12
  401b12:	4c 89 ed             	mov    rbp,r13
  401b15:	48 21 f5             	and    rbp,rsi
  401b18:	48 09 c5             	or     rbp,rax
  401b1b:	48 0f bc ed          	bsf    rbp,rbp
  401b1f:	48 8b 2c ed b0 63 56 00 	mov    rbp,QWORD PTR [rbp*8+0x5663b0]
  401b27:	4c 31 ed             	xor    rbp,r13
  401b2a:	48 09 fd             	or     rbp,rdi
  401b2d:	4c 89 ff             	mov    rdi,r15
  401b30:	48 21 f7             	and    rdi,rsi
  401b33:	48 83 cf 01          	or     rdi,0x1
  401b37:	48 0f bd ff          	bsr    rdi,rdi
  401b3b:	48 8b 04 fd b0 65 56 00 	mov    rax,QWORD PTR [rdi*8+0x5665b0]
  401b43:	4c 31 f8             	xor    rax,r15
  401b46:	48 89 df             	mov    rdi,rbx
  401b49:	48 21 f7             	and    rdi,rsi
  401b4c:	48 83 cf 01          	or     rdi,0x1
  401b50:	48 0f bd ff          	bsr    rdi,rdi
  401b54:	48 8b 3c fd b0 67 56 00 	mov    rdi,QWORD PTR [rdi*8+0x5667b0]
  401b5c:	48 31 df             	xor    rdi,rbx
  401b5f:	48 09 c7             	or     rdi,rax
  401b62:	4c 89 c8             	mov    rax,r9
  401b65:	48 21 f0             	and    rax,rsi
  401b68:	49 0f af c2          	imul   rax,r10
  401b6c:	48 d3 e8             	shr    rax,cl
  401b6f:	48 09 ef             	or     rdi,rbp
  401b72:	4c 01 d8             	add    rax,r11
  401b75:	48 3b 3c c5 58 b9 40 00 	cmp    rdi,QWORD PTR [rax*8+0x40b958]
  401b7d:	0f 85 65 01 00 00    	jne    401ce8 <main+0xa88>
  401b83:	48 8b 02             	mov    rax,QWORD PTR [rdx]
  401b86:	48 09 f0             	or     rax,rsi
  401b89:	48 0f af 42 f8       	imul   rax,QWORD PTR [rdx-0x8]
  401b8e:	48 c1 e8 34          	shr    rax,0x34
  401b92:	48 03 42 f0          	add    rax,QWORD PTR [rdx-0x10]
  401b96:	48 3b 3c c5 58 79 4b 00 	cmp    rdi,QWORD PTR [rax*8+0x4b7958]
  401b9e:	0f 85 5d 01 00 00    	jne    401d01 <main+0xaa1>
  401ba4:	4c 29 f6             	sub    rsi,r14
  401ba7:	4c 21 f6             	and    rsi,r14
  401baa:	0f 85 40 ff ff ff    	jne    401af0 <main+0x890>
  401bb0:	41 80 c0 01          	add    r8b,0x1
  401bb4:	41 80 f8 40          	cmp    r8b,0x40
  401bb8:	0f 85 d2 fe ff ff    	jne    401a90 <main+0x830>
  401bbe:	bf c0 90 56 00       	mov    edi,0x5690c0
  401bc3:	be ee 21 40 00       	mov    esi,0x4021ee
  401bc8:	ba 0c 00 00 00       	mov    edx,0xc
  401bcd:	e8 be f4 ff ff       	call   401090 <std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)@plt>
  401bd2:	bf c0 90 56 00       	mov    edi,0x5690c0
  401bd7:	be bb 6a 01 00       	mov    esi,0x16abb
  401bdc:	e8 7f f4 ff ff       	call   401060 <std::ostream& std::ostream::_M_insert<unsigned long>(unsigned long)@plt>
  401be1:	49 89 c6             	mov    r14,rax
  401be4:	48 8b 00             	mov    rax,QWORD PTR [rax]
  401be7:	48 8b 40 e8          	mov    rax,QWORD PTR [rax-0x18]
  401beb:	49 8b 9c 06 f0 00 00 00 	mov    rbx,QWORD PTR [r14+rax*1+0xf0]
  401bf3:	48 85 db             	test   rbx,rbx
  401bf6:	0f 84 37 01 00 00    	je     401d33 <main+0xad3>
  401bfc:	80 7b 38 00          	cmp    BYTE PTR [rbx+0x38],0x0
  401c00:	74 05                	je     401c07 <main+0x9a7>
  401c02:	8a 43 43             	mov    al,BYTE PTR [rbx+0x43]
  401c05:	eb 16                	jmp    401c1d <main+0x9bd>
  401c07:	48 89 df             	mov    rdi,rbx
  401c0a:	e8 91 f4 ff ff       	call   4010a0 <std::ctype<char>::_M_widen_init() const@plt>
  401c0f:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  401c12:	48 89 df             	mov    rdi,rbx
  401c15:	be 0a 00 00 00       	mov    esi,0xa
  401c1a:	ff 50 30             	call   QWORD PTR [rax+0x30]
  401c1d:	0f be f0             	movsx  esi,al
  401c20:	4c 89 f7             	mov    rdi,r14
  401c23:	e8 08 f4 ff ff       	call   401030 <std::ostream::put(char)@plt>
  401c28:	48 89 c7             	mov    rdi,rax
  401c2b:	e8 40 f4 ff ff       	call   401070 <std::ostream::flush()@plt>
  401c30:	bf c0 90 56 00       	mov    edi,0x5690c0
  401c35:	be fb 21 40 00       	mov    esi,0x4021fb
  401c3a:	ba 0c 00 00 00       	mov    edx,0xc
  401c3f:	e8 4c f4 ff ff       	call   401090 <std::basic_ostream<char, std::char_traits<char> >& std::__ostream_insert<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*, long)@plt>
  401c44:	bf c0 90 56 00       	mov    edi,0x5690c0
  401c49:	be bb 59 01 00       	mov    esi,0x159bb
  401c4e:	e8 0d f4 ff ff       	call   401060 <std::ostream& std::ostream::_M_insert<unsigned long>(unsigned long)@plt>
  401c53:	49 89 c6             	mov    r14,rax
  401c56:	48 8b 00             	mov    rax,QWORD PTR [rax]
  401c59:	48 8b 40 e8          	mov    rax,QWORD PTR [rax-0x18]
  401c5d:	49 8b 9c 06 f0 00 00 00 	mov    rbx,QWORD PTR [r14+rax*1+0xf0]
  401c65:	48 85 db             	test   rbx,rbx
  401c68:	0f 84 c5 00 00 00    	je     401d33 <main+0xad3>
  401c6e:	80 7b 38 00          	cmp    BYTE PTR [rbx+0x38],0x0
  401c72:	74 05                	je     401c79 <main+0xa19>
  401c74:	8a 43 43             	mov    al,BYTE PTR [rbx+0x43]
  401c77:	eb 16                	jmp    401c8f <main+0xa2f>
  401c79:	48 89 df             	mov    rdi,rbx
  401c7c:	e8 1f f4 ff ff       	call   4010a0 <std::ctype<char>::_M_widen_init() const@plt>
  401c81:	48 8b 03             	mov    rax,QWORD PTR [rbx]
  401c84:	48 89 df             	mov    rdi,rbx
  401c87:	be 0a 00 00 00       	mov    esi,0xa
  401c8c:	ff 50 30             	call   QWORD PTR [rax+0x30]
  401c8f:	0f be f0             	movsx  esi,al
  401c92:	4c 89 f7             	mov    rdi,r14
  401c95:	e8 96 f3 ff ff       	call   401030 <std::ostream::put(char)@plt>
  401c9a:	48 89 c7             	mov    rdi,rax
  401c9d:	e8 ce f3 ff ff       	call   401070 <std::ostream::flush()@plt>
  401ca2:	31 c0                	xor    eax,eax
  401ca4:	48 81 c4 28 02 00 00 	add    rsp,0x228
  401cab:	5b                   	pop    rbx
  401cac:	41 5c                	pop    r12
  401cae:	41 5d                	pop    r13
  401cb0:	41 5e                	pop    r14
  401cb2:	41 5f                	pop    r15
  401cb4:	5d                   	pop    rbp
  401cb5:	c3                   	ret    
  401cb6:	bf da 20 40 00       	mov    edi,0x4020da
  401cbb:	be 18 21 40 00       	mov    esi,0x402118
  401cc0:	b9 25 21 40 00       	mov    ecx,0x402125
  401cc5:	ba 26 00 00 00       	mov    edx,0x26
  401cca:	e8 81 f3 ff ff       	call   401050 <__assert_fail@plt>
  401ccf:	bf 3c 21 40 00       	mov    edi,0x40213c
  401cd4:	be 18 21 40 00       	mov    esi,0x402118
  401cd9:	b9 25 21 40 00       	mov    ecx,0x402125
  401cde:	ba 27 00 00 00       	mov    edx,0x27
  401ce3:	e8 68 f3 ff ff       	call   401050 <__assert_fail@plt>
  401ce8:	bf 7a 21 40 00       	mov    edi,0x40217a
  401ced:	be 18 21 40 00       	mov    esi,0x402118
  401cf2:	b9 25 21 40 00       	mov    ecx,0x402125
  401cf7:	ba 31 00 00 00       	mov    edx,0x31
  401cfc:	e8 4f f3 ff ff       	call   401050 <__assert_fail@plt>
  401d01:	bf b4 21 40 00       	mov    edi,0x4021b4
  401d06:	be 18 21 40 00       	mov    esi,0x402118
  401d0b:	b9 25 21 40 00       	mov    ecx,0x402125
  401d10:	ba 32 00 00 00       	mov    edx,0x32
  401d15:	e8 36 f3 ff ff       	call   401050 <__assert_fail@plt>
  401d1a:	bf b2 22 40 00       	mov    edi,0x4022b2
  401d1f:	be d3 22 40 00       	mov    esi,0x4022d3
  401d24:	b9 f5 22 40 00       	mov    ecx,0x4022f5
  401d29:	ba 23 00 00 00       	mov    edx,0x23
  401d2e:	e8 1d f3 ff ff       	call   401050 <__assert_fail@plt>
  401d33:	e8 78 f3 ff ff       	call   4010b0 <std::__throw_bad_cast()@plt>
  401d38:	0f 1f 84 00 00 00 00 00 	nop    DWORD PTR [rax+rax*1+0x0]

0000000000401d40 <__libc_csu_init>:
  401d40:	f3 0f 1e fa          	endbr64 
  401d44:	41 57                	push   r15
  401d46:	4c 8d 3d 83 70 16 00 	lea    r15,[rip+0x167083]        # 568dd0 <__frame_dummy_init_array_entry>
  401d4d:	41 56                	push   r14
  401d4f:	49 89 d6             	mov    r14,rdx
  401d52:	41 55                	push   r13
  401d54:	49 89 f5             	mov    r13,rsi
  401d57:	41 54                	push   r12
  401d59:	41 89 fc             	mov    r12d,edi
  401d5c:	55                   	push   rbp
  401d5d:	48 8d 2d 84 70 16 00 	lea    rbp,[rip+0x167084]        # 568de8 <__do_global_dtors_aux_fini_array_entry>
  401d64:	53                   	push   rbx
  401d65:	4c 29 fd             	sub    rbp,r15
  401d68:	48 83 ec 08          	sub    rsp,0x8
  401d6c:	e8 8f f2 ff ff       	call   401000 <_init>
  401d71:	48 c1 fd 03          	sar    rbp,0x3
  401d75:	74 1f                	je     401d96 <__libc_csu_init+0x56>
  401d77:	31 db                	xor    ebx,ebx
  401d79:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
  401d80:	4c 89 f2             	mov    rdx,r14
  401d83:	4c 89 ee             	mov    rsi,r13
  401d86:	44 89 e7             	mov    edi,r12d
  401d89:	41 ff 14 df          	call   QWORD PTR [r15+rbx*8]
  401d8d:	48 83 c3 01          	add    rbx,0x1
  401d91:	48 39 dd             	cmp    rbp,rbx
  401d94:	75 ea                	jne    401d80 <__libc_csu_init+0x40>
  401d96:	48 83 c4 08          	add    rsp,0x8
  401d9a:	5b                   	pop    rbx
  401d9b:	5d                   	pop    rbp
  401d9c:	41 5c                	pop    r12
  401d9e:	41 5d                	pop    r13
  401da0:	41 5e                	pop    r14
  401da2:	41 5f                	pop    r15
  401da4:	c3                   	ret    
  401da5:	66 66 2e 0f 1f 84 00 00 00 00 00 	data16 nop WORD PTR cs:[rax+rax*1+0x0]

0000000000401db0 <__libc_csu_fini>:
  401db0:	f3 0f 1e fa          	endbr64 
  401db4:	c3                   	ret    

Disassembly of section .fini:

0000000000401db8 <_fini>:
  401db8:	f3 0f 1e fa          	endbr64 
  401dbc:	48 83 ec 08          	sub    rsp,0x8
  401dc0:	48 83 c4 08          	add    rsp,0x8
  401dc4:	c3                   	ret    
