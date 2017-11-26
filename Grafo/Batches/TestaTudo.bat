REM Executa os testes de todos os scripts através dos constructos .exe

cls

if exist ..\Scripts\estatisticas.estat  del ..\Scripts\estatisticas.estat

..\Produto\Trab4-7	/s..\Scripts\TesteGrafo	/l..\Produto\Trab4-7	/a..\Scripts\estatisticas


..\Produto\Trab4-8	/s..\Scripts\TesteContador	/l..\Produto\Trab4-8	/a..\Scripts\estatisticas



..\..\Tools\exbestat /e..\Scripts\estatisticas
