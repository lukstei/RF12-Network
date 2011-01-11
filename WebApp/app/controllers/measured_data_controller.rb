require 'nokogiri'
require 'open-uri'

class MeasuredDataController < ApplicationController

	#POST /input 
<<<<<<< HEAD
	def create 
		doc = Nokogori::XML(params[:input]) 
=======
	def create
		render :text => params[:data])
>>>>>>> 46051896a7ddb23add88e4c84d854508e61899d8
	end 
	
end
