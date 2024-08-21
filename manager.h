#pragma once

#include <iostream>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkActor.h>
#include <vtkConeSource.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindowInteractor.h>
#include <emscripten/bind.h>

class Manager
{
public:
    Manager();

    void Init();
    void Start();

    void Terminate();
    void ReStart();

    void ChangeRenderWindow();
protected:
    vtkSmartPointer<vtkRenderWindowInteractor> m_renderWindowInteractor;
    vtkSmartPointer<vtkRenderWindow> m_renderWindow;
    vtkSmartPointer<vtkRenderer> m_renderer;
    vtkSmartPointer<vtkActor> m_actor;
};


EMSCRIPTEN_BINDINGS(Manager) {
    emscripten::class_<Manager>("Manager")
        .constructor()
        .function("Init", &Manager::Init)
        .function("Start", &Manager::Start)
        .function("ReStart", &Manager::ReStart)
        .function("Terminate", &Manager::Terminate)
        .function("ChangeRenderWindow", &Manager::ChangeRenderWindow);
};