import React from 'react';
import ReactDOM from 'react-dom';
import './index.css';
import App from './App';
import * as serviceWorker from './serviceWorker';

ReactDOM.render(
	<React.StrictMode>
		<App />
	</React.StrictMode>,
	document.getElementById('root')
);

//For working offline and loading faster, if necessary, change to register()
// and follow  https://bit.ly/CRA-PWA guidelines.
serviceWorker.unregister();
