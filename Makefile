# 編譯器
CXX := g++

# 編譯選項
CXXFLAGS := -O2 -Wall

# 原始碼
SRC := main.cpp

# 目標檔案名稱
TARGET := triangle

# Windows OpenGL + FreeGLUT 庫
LIBS := -lfreeglut -lopengl32 -lglu32
WINLIBS := -lgdi32 -luser32 -lwinmm

# -----------------------------
# 默認：動態連結
all: dynamic

# -----------------------------
# 動態連結版本
dynamic: $(SRC)
	$(CXX) $(CXXFLAGS) $< -o $(TARGET)_dyn.exe $(LIBS)

# -----------------------------
# 靜態連結版本
static: $(SRC)
	$(CXX) $(CXXFLAGS) -DFREEGLUT_STATIC $< -o $(TARGET)_static.exe -static $(LIBS) $(WINLIBS)

# -----------------------------
# 清除所有生成檔案
clean:
	rm -f $(TARGET)_*
