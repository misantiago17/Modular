REM Executa os testes de todos os scripts através dos constructos .exe

cls

if exist ..\Scripts\estatisticas.estat  del ..\Scripts\estatisticas.estat

..\Produto\TRAB4-1	/s..\Scripts\TestePerfil	/l..\Produto\TRAB4-1	/a..\Scripts\estatisticas


..\..\Tools\exbestat /e..\Scripts\estatisticas
