require 'nokogiri'
require 'open-uri'

class MeasuredDataController < ApplicationController

	#POST /input 
	def create
		render :text => params[:data])
	end 
	
end
