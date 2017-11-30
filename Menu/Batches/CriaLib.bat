@ECHO OFF
REM Copia arquivo lib de pasta comum "Biblioteca" para a pasta "Objetos".

pushd  .

cd ..
copy   ..\Biblioteca\ArcaboucoTeste.lib ..\Amizade\Objetos

popd