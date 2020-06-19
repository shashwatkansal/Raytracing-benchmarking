import React from 'react';
import Paper from '@material-ui/core/Paper';
import './App.css';
import DisplaySortedTable from './Table';
import Typography from '@material-ui/core/Typography';

function App() {
	return (
		<div className="App">
			<div className="content-wrap">
				<Paper
					style={{
						borderRadius: '5px',
						background: 'linear-gradient(45deg, #2667FF 30%, #c2d4ff 90%)',
						padding: '10px 0px'
					}}
				>
					<Typography variant="h2" style={{ color: '#FFFAFF' }}>
						Ray Tracing Animation Benchmarking
					</Typography>
				</Paper>
				<div className="intro">
					<Paper
						style={{
							borderRadius: '5px',
							padding: '10px 10px',
							paddingRight: '5%',
							paddingLeft: '5%'
						}}
						elevation={7}
					>
						<Intro />
					</Paper>
				</div>
				<div className="Table">
					<DisplaySortedTable />
				</div>
				<Footer />
			</div>
		</div>
	);

	function Footer() {
		return (
			<div className="main-footer">
				<Typography variant="h6">C Ray-Tracing Project</Typography>
				<Typography variant="subtitle1">
					by Shashwat Kansal, Sudarshan Sreeram, Rahul Gupta, Pranav Bansal
				</Typography>
			</div>
		);
	}
}

function Intro() {
	return (
		<div>
			<Typography variant="subtitle1">
				This is our project on Ray Tracing Animation Benchmarking. We've worked on multiple programs in C to
				bring together this project, such as an animation ray tracer, benchmarking program, and this node.js
				frontend to bring you the results of our project.
			</Typography>
		</div>
	);
}

export default App;
