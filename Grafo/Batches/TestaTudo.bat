REM Executa os testes de todos os scripts através dos constructos .exe

cls

if exist ..\Scripts\estatisticas.estat  del ..\Scripts\estatisticas.estat

..\Produto\Trab4-2	/s..\Scripts\TesteGrafo	/l..\Produto\Trab4-TesteGrafo	/a..\Scripts\estatisticas

..\Produto\Trab4-3	/s..\Scripts\TesteVerificadorSemDeturparcao	/l..\Produto\Trab4-TesteVerificadorSemDeturparcao	/a..\Scripts\estatisticas

..\Produto\Trab4-3	/s..\Scripts\TesteVerificadorComDeturparcao	/l..\Produto\Trab4-TesteVerificadorComDeturparcao	/a..\Scripts\estatisticas

..\Produto\Trab4-3	/s..\Scripts\TesteControleEspaco	       /l..\Produto\Trab4-TesteControleEspaco				/a..\Scripts\estatisticas

..\Produto\Trab4-3	/s..\Scripts\TesteContador			/l..\Produto\Trab4-TesteContador					/a..\Scripts\estatisticas

..\..\Tools\exbestat /e..\Scripts\estatisticas
