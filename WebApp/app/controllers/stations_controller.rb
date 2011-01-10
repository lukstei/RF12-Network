class StationsController < ApplicationController
	
	# GET \stations
	def index
        @stations = Station.all
		
		respond_to do |format|
			format.html 
		end 
	end 
	
	# GET \stations\id 
	def show
		@station = Station.find(params[:id])
		
		respond_to do |format|
			format.html 
		end
	end 
	
	def new
		@station = Station.new
		
		respond_to do |format|
			format.html 
		end 
	end 
	
	def edit
		@station = Station.find(params[:id])
	end
	
	# POST \stations
	def create
		@station = Station.new(params[:station])
		@station.save
		
		respond_to do |format|
			format.html
		end
	end 
	
end
