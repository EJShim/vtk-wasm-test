import {default as managerModule} from './build/manager.js'


async function main(){
    console.log("main function");

    let app = await managerModule();
    let manager = new app.Manager();

    
    manager.Init();
    manager.Start();


}

main()


