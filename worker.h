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
    vtkSmartPointer<vtkRenderWindowInteractor> m_renderWindowInteractor;
    vtkSmartPointer<vtkRenderWindow> m_renderWindow;
    vtkSmartPointer<vtkRenderer> m_renderer;
    vtkSmartPointer<vtkActor> m_actor;
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