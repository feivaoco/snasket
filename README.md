# SNASKET
Titulo inspirado en "Caskets" del NehruvianDOOM


![gif_snasket_1699308142](https://github.com/feivaoco/assets_repositorios/assets/52841258/fc949eb9-1656-4ec4-84e9-222e28591ceb)


## Advertencia
Tienes que poner en comentario las siguientes lineas de codigo para que compile con gcc.
Esto porque raylib tiene conflictos con windows.h, este lo usa libmysql. Igualmente como no
se compila nada de windows.h entonces no habra problemas si se comentan. 
Tambien voy a resaltar que dejare de usar raylib hasta que arreglen ese problema, intente compilar desde
el source code pero mi compu sigue dando problemas de path not found cuando le doy a make en el src del
raylib.

En el archivo winuser.h
- Linea 3760 la función ShowCursor(WINBOOL bShow);
- Linea 3479 a 3482 las funciones DrawTextA, DrawTextW, DrawTextExA, DrawTextExW
- Linea 2282 la función CloseWindow
- Linea 4200 a 4208 del #define LoadImage a la funcion GetIconInfo 

En el archivo wingdi.h
- Linea 3158 la funcion Rectangle

##### raylib
<https://github.com/raysan5/raylib>
##### libpd
<https://github.com/libpd/libpd>
##### portaudio
<https://github.com/PortAudio/portaudio>
##### msf_gif
<https://github.com/notnullnotvoid/msf_gif>


###### Todas las dependencias se encuentran en este mismo repositorio
###### El compilador utilizado de gcc es del [w64devkit](https://github.com/skeeto/w64devkit).
###### Al igual que el GNU Make es parte de ese kit.

El proyecto es una prueba de porfin hacer un jueguito en raylib e integrar Pure Data mediante la libreria de libpd. 

Si no peudes compilar aunque estes usando w64devkit entonces debes
realizar lo siguiente:
1. Descargar el codigo fuente de libpd y seguir sus instrucciones de compilacion
2. Colocar los archivos resultado de la compilacion en sus respectivas carpetas en este proyecto
3. Descargar el codigo fuente de portaudio y compilarlo
4. Colocar los archivos resultado de la compilacion en sus respectivas carpetas en este proyecto   
