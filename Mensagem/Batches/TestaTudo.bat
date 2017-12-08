REM Executa os testes de todos os scripts através dos constructos .exe

cls

if exist ..\Scripts\estatisticas.estat  del ..\Scripts\estatisticas.estat

..\Produto\TRAB4-5	/s..\Scripts\TesteMensagem	/l..\Produto\TRAB4-5	/a..\Scripts\estatisticas


..\..\Tools\exbestat /e..\Scripts\estatisticas
