#include "manager.h"
#include <vtkProperty.h>
#include <vtkInteractorStyleTrackballCamera.h>

Manager::Manager()
{
    m_renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    m_renderWindowInteractor->SetInteractorStyle(vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New());
    m_renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    m_renderer = vtkSmartPointer<vtkRenderer>::New();

    vtkIndent indent;

    m_renderWindowInteractor->PrintSelf(std::cout, indent);
}

void Manager::Init()
{
    vtkNew<vtkConeSource> cone;
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection( cone->GetOutputPort() );

    m_actor = vtkSmartPointer<vtkActor>::New();
    m_actor->SetMapper( mapper );

    m_renderer->AddActor(m_actor);
    m_renderer->SetBackground( 0, 0, 0 );

    m_renderWindow->AddRenderer( m_renderer );
    m_renderWindowInteractor->SetRenderWindow( m_renderWindow );

    m_renderer->ResetCamera();
    m_renderWindow->Render();

    std::cout << "Init!\n";
}

/**
 * @brief   the interface is used in web page
 * 
 * @return  nothing
 */
void Manager::ChangeRenderWindow()
{
    //m_RenderWindowInteractor->TerminateApp();
    
    std::cout << "m_Renderer: " << m_renderer << std::endl;
    std::cout << "m_RenderWindowInteractor: " << m_renderWindowInteractor << std::endl;


    m_actor->GetProperty()->SetColor(1,0,0);

    m_renderWindow->Render();

}

void Manager::Start()
{
    m_renderWindowInteractor->Start();

    std::cout << "Start!\n";
}

void Manager::Terminate()
{
    m_renderWindowInteractor->TerminateApp(); // same to emscripten_cancel_main_loop
}

void Manager::ReStart()
{
    m_renderWindowInteractor->ReInitialize();
    m_renderWindowInteractor->Start();
}