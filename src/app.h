#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class App
{
public:

	// constructors 
	// ------------
	App() = default;
	App(const App&) = delete;
	App& operator=(const App&) = delete;
	
	// 
	// Jeśli mamy konstruktor kopiujący, to przenoszący nie będzie tworzony automatycznie
	// https://stackoverflow.com/questions/23771194/why-should-i-delete-move-constructor-and-move-assignment-operator-in-a-singleton
	//
	// App(App&&) = delete;
	// App& operator=(App&&) = delete;


	// methods
	// -------
	int init();
	void runMainLoop();
	void terminate();

private:

	GLFWwindow* m_window;
};