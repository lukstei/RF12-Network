class TasksController < ApplicationController

	# GET \tasks
	def index
		@tasks = Task.all
		
		respond_to do |format|
			format.html
		end 
	end
	
	def new
		@task = Task.new
		
		respond_to do |format|
			format.html 
		end 
	end
	
	def show
		@task = Task.find(params[:id])
		
		respond_to do |format|
			format.html 
		end 
	end 
	
	def edit
		@task = Task.find(params[:id])
	end
	
	#POST /tasks
	def create
		@task = Task.new(params[:task])
		
		respond_to do |format|
			if @task.save		
				format.html { redirect_to @task, :notice => 'Task erfolgreich erstellt' }
			else	
				format.html { render :action => "new" }
			end
		end 
	end 
		
	def update
		@task = Task.find(params[:id])
		
		respond_to do |format|
			if @task.update_attributes(params[:task])
				format.html { redirect_to @task, :notice => 'Änderungen erfolgreich gespeichert' }
			else
				format.html { render :action => "edit" }
			end
		end 
	end 
	
	def destroy
		@task = Task.find(params[:id])
		@task.destroy
		
		respond_to do |format|
			format.html { redirect_to(tasks_url) }
		end 
	end 
	
end
