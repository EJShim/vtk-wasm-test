#include "worker.h"
#include <vtkProperty.h>

Worker::Worker()
{
    m_RenderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    m_RenderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    m_Renderer = vtkSmartPointer<vtkRenderer>::New();

    vtkIndent indent;

    m_RenderWindowInteractor->PrintSelf(std::cout, indent);
}

void Worker::Init()
{
    vtkNew<vtkConeSource> cone;
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection( cone->GetOutputPort() );

    m_Actor = vtkSmartPointer<vtkActor>::New();
    m_Actor->SetMapper( mapper );

    m_Renderer->AddActor(m_Actor);
    m_Renderer->SetBackground( 0, 0, 0 );

    m_RenderWindow->AddRenderer( m_Renderer );
    m_RenderWindowInteractor->SetRenderWindow( m_RenderWindow );

    m_Renderer->ResetCamera();
    m_RenderWindow->Render();

    std::cout << "Init!\n";
}

/**
 * @brief   the interface is used in web page
 * 
 * @return  nothing
 */
void Worker::ChangeRenderWindow()
{
    //m_RenderWindowInteractor->TerminateApp();
    
    std::cout << "m_Renderer: " << m_Renderer << std::endl;
    std::cout << "m_RenderWindowInteractor: " << m_RenderWindowInteractor << std::endl;


    m_Actor->GetProperty()->SetColor(1,0,0);

    m_RenderWindow->Render();

}

void Worker::Start()
{
    m_RenderWindowInteractor->Start();

    std::cout << "Start!\n";
}

void Worker::Terminate()
{
    m_RenderWindowInteractor->TerminateApp(); // same to emscripten_cancel_main_loop
}

void Worker::ReStart()
{
    m_RenderWindowInteractor->ReInitialize();
    m_RenderWindowInteractor->Start();
}