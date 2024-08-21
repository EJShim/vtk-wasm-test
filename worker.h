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

class Worker
{
public:
    Worker();

    void Init();
    void Start();

    void Terminate();
    void ReStart();

    void ChangeRenderWindow();
protected:
    vtkSmartPointer<vtkRenderWindowInteractor> m_RenderWindowInteractor;
    vtkSmartPointer<vtkRenderWindow> m_RenderWindow;
    vtkSmartPointer<vtkActor> m_Actor;
    vtkSmartPointer<vtkRenderer> m_Renderer;

};


EMSCRIPTEN_BINDINGS(worker) {
    emscripten::class_<Worker>("Worker")
        .constructor()
        .function("Init", &Worker::Init)
        .function("Start", &Worker::Start)
        .function("ReStart", &Worker::ReStart)
        .function("Terminate", &Worker::Terminate)
        .function("ChangeRenderWindow", &Worker::ChangeRenderWindow);
};