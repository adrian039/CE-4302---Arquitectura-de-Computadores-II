# Taller 2 - Arquitectura de Computadores II 

## Comandos para correr cada archivo

### SAXPY Serial

Para compilarlo incluir el archivo saxpy.c en la carpeta jni/:
Cambiar la linea 5 y 7 del archivo Android.mk por:

```bash
 LOCAL_MODULE := saxpy
 LOCAL_SRC_FILES := saxpy.c
```
y en el archivo Application.mk cambiar la linea 2 por:

```bash
APP_MODULES := saxpy cpufeatures
```
y ejecutar los siguientes comandos:

```bash
~ /opt/android-ndk-r19c/ndk-build
~ adb push ../libs/armeabi-v7a/saxpy /data/local/tmp
~ adb shell /data/local/tmp/saxpy
````

### SAXPY Paralelo
Para compilarlo incluir el archivo saxpy_par.c en la carpeta jni/:
Cambiar la linea 5 y 7 del archivo Android.mk por:

```bash
 LOCAL_MODULE := saxpy_par
 LOCAL_SRC_FILES := saxpy_par.c
```
y en el archivo Application.mk cambiar la linea 2 por:

```bash
APP_MODULES := saxpy_par cpufeatures
```
y ejecutar los siguientes comandos:

```bash
~ /opt/android-ndk-r19c/ndk-build
~ adb push ../libs/armeabi-v7a/saxpy_par /data/local/tmp
~ adb shell /data/local/tmp/saxpy_par
````


### Multiplicación de Matrices 
Para compilarlo incluir el archivo FloatMM.c en la carpeta jni/:
Cambiar la linea 5 y 7 del archivo Android.mk por:

```bash
 LOCAL_MODULE := FloatMM
 LOCAL_SRC_FILES := FloatMM.c
```
y en el archivo Application.mk cambiar la linea 2 por:

```bash
APP_MODULES := FloatMM cpufeatures
```
y ejecutar los siguientes comandos:

```bash
~ /opt/android-ndk-r19c/ndk-build
~ adb push ../libs/armeabi-v7a/FloatMM /data/local/tmp
~ adb shell /data/local/tmp/FloatMM
````