#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glew.h>
#include <glfw3.h>
#include <math.h>
#include <time.h>
//Dimensiones de la ventana
const int WIDTH = 800, HEIGHT = 800;
GLuint VAO, VBO, shader;
float rojo=0.0f, verde=0.5f, azul=0.1f;

//LENGUAJE DE SHADER (SOMBRAS) GLSL
//Vertex Shader
//recibir color, salida Vcolor
static const char* vShader = "						\n\
#version 330										\n\
layout (location =0) in vec3 pos;					\n\
void main()											\n\
{													\n\
gl_Position=vec4(pos.x,pos.y,pos.z,1.0f); 			\n\
}";

//Fragment Shader
//recibir Vcolor y dar de salida color
static const char* fShader = "						\n\
#version 330										\n\
out vec4 color;										\n\
void main()											\n\
{													\n\
	color = vec4(0.7f,0.0f,0.0f,1.0f);	 			\n\
}";



void CrearTriangulo()
{
	GLfloat vertices[] = {
		// Barra vertical (derecha de la J) — llega hasta y = 0.05
		-0.70f, 0.90f, 0.0f,
		-0.65f, 0.90f, 0.0f,
		-0.70f, 0.10f, 0.0f,

		-0.65f, 0.90f, 0.0f,
		-0.65f, 0.10f, 0.0f,
		-0.70f, 0.10f, 0.0f,

		// Base / gancho de la J (horizontal, conecta con la vertical)
		-0.95f, 0.15f, 0.0f,
		-0.65f, 0.15f, 0.0f,
		-0.95f, 0.10f, 0.0f,

		-0.65f, 0.15f, 0.0f,
		-0.65f, 0.10f, 0.0f,
		-0.95f, 0.10f, 0.0f,

		-0.90f, 0.20f, 0.0f,
		-0.90f, 0.10f, 0.0f,
		-0.95f, 0.10f, 0.0f,

		-0.95f, 0.20f, 0.0f,
		-0.90f, 0.20f, 0.0f,
		-0.95f, 0.10f, 0.0f,

		//---------------- O ----------------
		// Parte superior
		-0.60f, 0.9f, 0.0f,
		-0.30f, 0.9f, 0.0f,
		-0.60f, 0.85f, 0.0f,

		-0.30f, 0.9f, 0.0f,
		-0.30f, 0.85f, 0.0f,
		-0.60f, 0.85f, 0.0f,

		// Parte inferior
		-0.60f, 0.15f, 0.0f,
		-0.30f, 0.15f, 0.0f,
		-0.60f, 0.10f, 0.0f,

		-0.30f, 0.15f, 0.0f,
		-0.30f, 0.10f, 0.0f,
		-0.60f, 0.10f, 0.0f,

		// Lateral izquierdo
		-0.60f, 0.9f, 0.0f,
		-0.55f, 0.9f, 0.0f,
		-0.60f, 0.10f, 0.0f,

		-0.55f, 0.9f, 0.0f,
		-0.55f, 0.10f, 0.0f,
		-0.60f, 0.10f, 0.0f,

		// Lateral derecho
		-0.35f, 0.9f, 0.0f,
		-0.30f, 0.9f, 0.0f,
		-0.35f, 0.10f, 0.0f,

		-0.30f, 0.9f, 0.0f,
		-0.30f, 0.10f, 0.0f,
		-0.35f, 0.10f, 0.0f,

		//---------------- E ----------------
		// Palito vertical
		-0.20f, 0.9f, 0.0f,
		-0.15f, 0.9f, 0.0f,
		-0.20f, 0.1f, 0.0f,

		-0.15f, 0.9f, 0.0f,
		-0.15f, 0.1f, 0.0f,
		-0.20f, 0.1f, 0.0f,

		// Línea superior
		-0.20f, 0.9f, 0.0f,
		0.05f, 0.9f, 0.0f,
		-0.20f, 0.85f, 0.0f,

		0.05f, 0.9f, 0.0f,
		0.05f, 0.85f, 0.0f,
		-0.20f, 0.85f, 0.0f,

		// Línea del medio
		-0.20f, 0.55f, 0.0f,
		0.00f, 0.55f, 0.0f,
		-0.20f, 0.50f, 0.0f,

		0.00f, 0.55f, 0.0f,
		0.00f, 0.50f, 0.0f,
		-0.20f, 0.50f, 0.0f,

		// Línea inferior
		-0.20f, 0.15f, 0.0f,
		0.05f, 0.15f, 0.0f,
		-0.20f, 0.10f, 0.0f,

		0.05f, 0.15f, 0.0f,
		0.05f, 0.10f, 0.0f,
		-0.20f, 0.10f, 0.0f,
	};
	glGenVertexArrays(1, &VAO); //generar 1 VAO
	glBindVertexArray(VAO);//asignar VAO

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //pasarle los datos al VBO asignando tamano, los datos y en este caso es estático pues no se modificarán los valores

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);//Stride en caso de haber datos de color por ejemplo, es saltar cierta cantidad de datos
		glEnableVertexAttribArray(0);
		//agregar valores a vèrtices y luego declarar un nuevo vertexAttribPointer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

}
void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) //Función para agregar los shaders a la tarjeta gráfica

//the Program recibe los datos de theShader

{
	GLuint theShader = glCreateShader(shaderType);//theShader es un shader que se crea de acuerdo al tipo de shader: vertex o fragment
	const GLchar* theCode[1];
	theCode[0] = shaderCode;//shaderCode es el texto que se le pasa a theCode
	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);//longitud del texto
	glShaderSource(theShader,1, theCode, codeLength);//Se le asigna al shader el código
	glCompileShader(theShader);//Se comila el shader
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	//verificaciones y prevención de errores
	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al compilar el shader %d es: %s \n",shaderType, eLog);
		return;
	}
	glAttachShader(theProgram, theShader);//Si no hubo problemas se asigna el shader a theProgram el cual asigna el código a la tarjeta gráfica
}

void CompileShaders() {
	shader= glCreateProgram(); //se crea un programa
	if (!shader)
	{
		printf("Error creando el shader");
		return;
	}
	AddShader(shader, vShader, GL_VERTEX_SHADER);//Agregar vertex shader
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);//Agregar fragment shader
	//Para terminar de linkear el programa y ver que no tengamos errores
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	glLinkProgram(shader);//se linkean los shaders a la tarjeta gráfica
	 //verificaciones y prevención de errores
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al linkear es: %s \n", eLog);
		return;
	}
	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al validar es: %s \n", eLog);
		return;
	}



}
int main()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}

	//****  LAS SIGUIENTES 4 LÍNEAS SE COMENTAN EN DADO CASO DE QUE AL USUARIO NO LE FUNCIONE LA VENTANA Y PUEDA CONOCER LA VERSIÓN DE OPENGL QUE TIENE ****/

	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Primer ventana", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	int BufferWidth, BufferHeight;
	glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Asignar valores de la ventana y coordenadas
	//Asignar Viewport
	glViewport(0, 0, BufferWidth, BufferHeight);

 //Llamada a las funciones creadas antes del main
	CrearTriangulo();
	CompileShaders();

	//Utilizamos time y la inicialización del random
	srand(time(NULL));	
	time_t last = time(NULL);
	//Loop mientras no se cierra la ventana
	while (!glfwWindowShouldClose(mainWindow))
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		time_t now = time(NULL);
		if (now - last >= 2) {              // han pasado 2 segundos
			float newR, newG, newB;
			//Generar un color suficientemente distinto al actual
			do {
				newR = rand() / (float)RAND_MAX; //0.0 - 1.0
				newG = rand() / (float)RAND_MAX;
				newB = rand() / (float)RAND_MAX;
				//suma de diferencias en canales para garantizar cambio notable
			} while (fabs(newR - rojo) + fabs(newG - verde) + fabs(newB - azul) < 0.35f);

			rojo = newR;
			verde = newG;
			azul = newB;

			last = now;
		}
		//Limpiar la ventana
		glClearColor(rojo,verde,azul,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES,0, 66);
		glBindVertexArray(0);

		glUseProgram(0);

		glfwSwapBuffers(mainWindow);
		 
		//NO ESCRIBIR NINGUNA LÍNEA DESPUÉS DE glfwSwapBuffers(mainWindow); 
	}


	return 0;
}