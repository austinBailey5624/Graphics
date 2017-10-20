CPP = g++ -std=c++11
INC = -I../cryphutil -I../fontutil -I../glslutil -I../mvcutil
C_FLAGS = -fPIC -g -c -DGL_GLEXT_PROTOTYPES $(INC)

LINK = g++ -fPIC -g
LOCAL_UTIL_LIBRARIES = ../lib/libcryph.so ../lib/libfont.so ../lib/libglsl.so ../lib/libmvc.so
GL_LIB_LOC = -L/usr/lib/nvidia-375
GL_LIBRARIES = $(GL_LIB_LOC) -lglfw -lGLU -lGL

OBJS = project2.o ModelView_Additions.o Block.o Table.o RubiksBlock.o Cylinder.o Chair.o RubiksCube.o

project2: $(OBJS) $(LOCAL_UTIL_LIBRARIES)
	$(LINK) -o project2 $(OBJS) $(LOCAL_UTIL_LIBRARIES) $(GL_LIBRARIES)

../lib/libcryph.so: ../cryphutil/AffVector.h ../cryphutil/AffVector.c++ ../cryphutil/AffPoint.h ../cryphutil/AffPoint.c++
	(cd ../cryphutil; make)

../lib/libfont.so: ../fontutil/CFont.h ../fontutil/CFont.c++ ../fontutil/CGLString.h ../fontutil/CGLString.c++
	(cd ../fontutil; make)

../lib/libglsl.so: ../glslutil/ShaderIF.h ../glslutil/ShaderIF.c++
	(cd ../glslutil; make)

../lib/libmvc.so: ../mvcutil/Controller.h ../mvcutil/Controller.c++ ../mvcutil/ModelView.h ../mvcutil/ModelView.c++
	(cd ../mvcutil; make)

project2.o: project2.c++
	$(CPP) $(C_FLAGS) project2.c++
ModelView_Additions.o: ModelView_Additions.c++
	$(CPP) $(C_FLAGS) ModelView_Additions.c++

RectPrism.o: RectPrism.h RectPrism.c++
	$(CPP) $(C_FLAGS) RectPrism.c++

Block.o: Block.h Block.c++
	$(CPP) $(C_FLAGS) Block.c++

Table.o: Table.h Table.c++ Block.h Block.c++
	$(CPP) $(C_FLAGS) Table.c++ Block.c++

RubiksBlock.o: RubiksBlock.h RubiksBlock.c++ Block.h Block.c++
	$(CPP) $(C_FLAGS) RubiksBlock.c++ Block.c++

Cylinder.o: Cylinder.h Cylinder.c++
	$(CPP) $(C_FLAGS) Cylinder.c++

Chair.o: Chair.h Chair.c++ Cylinder.h Cylinder.c++ Block.h Block.c++
	$(CPP) $(C_FLAGS) Chair.c++ Cylinder.c++ Block.c++

RubiksCube.o: RubiksCube.h RubiksCube.c++ RubiksBlock.h RubiksBlock.c++
	$(CPP) $(C_FLAGS) RubiksCube.c++ RubiksBlock.c++

clean:
	rm *.o project2
