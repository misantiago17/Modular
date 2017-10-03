REM Executa os testes de todos os scripts através dos constructos .exe

cls

if exist ..\Scripts\estatisticas.estat  del ..\Scripts\estatisticas.estat

..\Produto\TesteLista	/s..\Scripts\TesteLista	/l..\Produto\TesteLista	/a..\Scripts\estatisticas


..\..\Tools\exbestat /e..\Scripts\estatisticas
